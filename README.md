# Smart Shopping Cart –  *Tap Cart*

## Youtube link demo
https://youtu.be/8iXMl7V7iCE


## Project Overview
The Tap Cart is an embedded system project. This device is designed to modernize the retail shopping experience by automatically detecting, tracking, and managing items placed in or removed from the cart, reducing checkout times and improving customer convenience.

## Hardware Components
The following hardware modules were integrated into our project:
- **NXP Freedom K66F Board** – Acts as the central controller (Cortex M4-based).
- **ESP32 Wi-Fi Module** – Sends shopping cart data/object images to a cloud databases.
- **Arducam Mega Camera** – Captures images for item detection using an AI model.
- **4-Line I2C LCD Display** – Displays cart contents and prices.
- **RGB LED** – Indicates item scan status with color codes. [Green -> Active, Red -> Inactive]
- **Speaker** – Provides audio feedback for actions (item added/removed, errors,activation/deactivation).
- **RFID-RC522 Reader** – Acts as a payment method that enables user authentication and enable the cart’s active state.

## AI Integration
Captured images are sent via the ESP32 to a Firebase Cloud Function that runs a pre-trained AI object detection model. The identified item is sent back to the K66F board via the ESP32 and update and displayed on the LCD.

## Project Goals
- Eliminate the need for traditional checkout lines.
- Create a seamless and interactive shopping experience.
- Ensure reliability through multi-interface hardware integration and real-time AI detection.

## Output Delivery
The final cart content and cost are displayed on the LCD and also sent to the user's mobile interface via the ESP32 Wi-Fi connection.

---

Developers: Abhi Patel & Inderpreet Singh Parmar
