# Hand Gesture Controlled LEDs with ESP32

This project uses hand gesture recognition to control LEDs, connected to ESP32 microcontroller. 
The hand gestures are detected using a webcam and the `cvzone` library. 
The detected gestures are then sent to the ESP32, which lights up the corresponding LEDs and displays the received data on an OLED screen.

## Requirements

- Python
- ESP32 microcontroller
- 5x LEDs
- OLED screen
- Webcam

## Python Dependencies

Install the required Python libraries using the following command:
pip install -r requirements.txt

## C++ Dependencies

For ESP32 setup ensure you have the necessary libraries installed in your Arduino IDE:
- WiFi
- Adafruit GFX Library
- Adafruit SSD1306

## Usage

1) Upload esp32_hand_recog.ino to your ESP32 microcontroller
2) Run `controller.py` script 
3) Run `hand_recog.py` script to start capturing hand gestures.
 