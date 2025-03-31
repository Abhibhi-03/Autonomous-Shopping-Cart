#include "PinNames.h"
#include "mbed.h"
#include "LCDi2c.h"
#include "MFRC522.h"

// Define LED GPIO pins
DigitalOut greenLED(PTC12); // External Green LED to show system active
DigitalOut redLED(PTC8);   // External Red LED to show system inactive

// Serial communication for debugging/input (optional)
UnbufferedSerial pc(USBTX, USBRX, 9600); // TX, RX, Baud rate

LCDi2c lcd(PTB3, PTB2, LCD20x4); // Initialize the LCD using i2c [SDA, SCL]

// RFID module setup
MFRC522 RfChip(PTD2, PTD3, PTD1, PTC11, PTD0); // Initialise the RFID using SPI [MOSI,MISO, SCK, SDA, RST]

// Function to compute string length (since strlen() may not work)
int stringLength(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Function to update the LCD display
void updateLCD(const char* message, int duration_ms) {
    lcd.cls(); // Clear LCD before displaying new message
    int len = stringLength(message);
    int maxColumns = 20; // LCD width in columns

    if (len <= maxColumns) {
        lcd.locate(0, 0);
        lcd.printf("%s", message);
        if (duration_ms > 0) {
            ThisThread::sleep_for(std::chrono::milliseconds(duration_ms));
            lcd.cls();
        }
    } else {
        // Scrolling message
        int shift = 0;
        if (duration_ms == -1) {
            while (true) { 
                lcd.cls();
                lcd.locate(0, 0);
                for (int i = 0; i < maxColumns; ++i) {
                    lcd.putc(message[(i + shift) % len]);
                }
                shift++;
                ThisThread::sleep_for(300ms);
            }
        } else {
            for (int j = 0; j < duration_ms / 300; j++) {
                lcd.cls();
                lcd.locate(0, 0);
                for (int i = 0; i < maxColumns; ++i) {
                    lcd.putc(message[(i + shift) % len]);
                }
                shift++;
                ThisThread::sleep_for(300ms);
            }
            lcd.cls();
        }
    }
}

// Function to update system status (LEDs & LCD)
void updateStatusIndicator(bool systemActive) {
    if (systemActive) {
        redLED = 0;   // Turn OFF red LED
        greenLED = 1; // Turn ON green LED
        updateLCD("Cart System Active", -1);
    } else {
        redLED = 1;   // Turn ON red LED
        greenLED = 0; // Turn OFF green LED
        updateLCD("Cart System Inactive", -1);
    }
}

// Function to detect RFID card tap
bool detectRFID() {
    if (!RfChip.PICC_IsNewCardPresent() || !RfChip.PICC_ReadCardSerial()) {
        return false; // No card detected
    }

    // Print Card UID for debugging
    // printf("Card UID: ");
    // for (uint8_t i = 0; i < RfChip.uid.size; i++) {
    //     printf(" %02X", RfChip.uid.uidByte[i]);
    // }
    // printf("\n");

    RfChip.PICC_HaltA(); // Halt communication
    return true; // Card detected
}

int main() {
    // Initialize LCD
    printf("LCD Initialization...\n");
    updateLCD("WELCOME TO SMART CART, PLEASE TAP CARD TO AUTHORISE PAYMENT", 10000);

    // Initialize RFID
    RfChip.PCD_Init();
    printf("RFID Initialized...\n");

    // Initialize LEDs
    // redLED = 1;
    // greenLED = 0;
    updateStatusIndicator(false);

    while (true) {
        // if (detectRFID()) {
        //     printf("RFID Card Detected!\n");
        //     greenLED = !greenLED;
        //     printf("SYSTEM STATUS: ACTIVE\n");
        //     redLED = !redLED;
        //     updateLCD("Card Scanned, Thank you for shopping!", 10000);
        // }
        if (detectRFID()) { // Detect RFID tap to toggle cart state
            static bool systemActive = false;
            systemActive = !systemActive;
            updateStatusIndicator(systemActive);
        }
        ThisThread::sleep_for(500ms);
    }
}
