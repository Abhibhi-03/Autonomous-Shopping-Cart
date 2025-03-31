#include "mbed.h"

DigitalOut buzzer(PTC16);  // Working pin

int main() {
    while (true) {
        buzzer = 1;                    // Turn buzzer ON
        ThisThread::sleep_for(100ms); // Beep duration
        buzzer = 0;                    // Turn buzzer OFF

        ThisThread::sleep_for(2s);    // Wait 2 seconds before next beep
    }
}
