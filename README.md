# Patient Monitoring System

## Overview

This project implements a patient monitoring system using Arduino and Blynk. The system measures the patient's heart rate, temperature, and SpO2 levels, displaying the readings on an LCD screen and sending data to the Blynk app. If any of the measured values exceed the predefined thresholds, an alarm buzzer is activated.

## Features

- Real-time heart rate monitoring
- Temperature measurement
- SpO2 level measurement
- Data display on an LCD screen
- Remote monitoring via Blynk app
- Alarm buzzer for critical values

## Prerequisites

Before you begin, ensure you have met the following requirements:

- Arduino board (e.g., Arduino Uno)
- LCD screen
- Pulse sensor
- LM35 temperature sensor
- SpO2 sensor
- Buzzer
- Blynk app
- SoftwareSerial library
- Blynk library
- LiquidCrystal library

## Hardware Setup

1. **Connections:**
    - **Pulse Sensor:**
        - Signal pin to A0
        - VCC to 5V
        - GND to GND
    - **LM35 Temperature Sensor:**
        - Output pin to A1
        - VCC to 5V
        - GND to GND
    - **SpO2 Sensor:**
        - Signal pin to A2
        - VCC to 5V
        - GND to GND
    - **Buzzer:**
        - Positive pin to digital pin 8
        - Negative pin to GND
    - **LCD:**
        - RS to pin 2
        - Enable to pin 3
        - D4 to pin 4
        - D5 to pin 5
        - D6 to pin 6
        - D7 to pin 7

2. **Arduino to Computer:**
    - Connect the Arduino board to your computer via USB.

## Software Setup

1. **Clone this repository:**
    ```sh
    git clone https://github.com/omkarpawar201/Patient-monitoring-system.git
    cd patient-monitoring-system
    ```

2. **Install Required Libraries:**
    - Open the Arduino IDE and go to `Sketch` > `Include Library` > `Manage Libraries`.
    - Search for and install the following libraries:
        - Blynk
        - SoftwareSerial
        - LiquidCrystal

3. **Configure Blynk:**
    - Create a new project in the Blynk app.
    - Note the `AUTH_TOKEN` provided by Blynk.
    - Replace the `BLYNK_TEMPLATE_ID`, `BLYNK_TEMPLATE_NAME`, and `BLYNK_AUTH_TOKEN` in the sketch with your own values.

## Usage

1. **Upload the Code:**
    - Open the `patient_monitoring_system.ino` file in the Arduino IDE.
    - Replace the placeholders with your Blynk credentials.
    - Upload the code to your Arduino board.

2. **Run the System:**
    - Open the Serial Monitor in the Arduino IDE to debug and see the outputs.
    - The LCD will display heart rate (BPM) and temperature (°C).
    - The Blynk app will show real-time data of BPM, temperature, and SpO2 levels.
    - If the heart rate exceeds 150 BPM, temperature exceeds 50°C, or SpO2 level is below 90%, the buzzer will sound an alarm.

## References

- [Blynk Library](https://github.com/blynkkk/blynk-library)
- [SoftwareSerial Library](https://www.arduino.cc/en/Reference/SoftwareSerial)
- [LiquidCrystal Library](https://www.arduino.cc/en/Reference/LiquidCrystal)