# IoT Sensor Wearable Project

## Overview

This project implements an IoT wearable device that incorporates BME280 and MPU6050 sensors. The device measures environmental parameters and user motion to provide real-time data. It includes a variety of features such as vibration alerts, LED indicators, and an OLED display for information visualization.

## Features

1. **Environmental Monitoring:**
   - Reads temperature, pressure, and humidity data from the BME280 sensor.
   - Displays the sensor data on the OLED screen.

2. **Motion Sensing:**
   - Utilizes the MPU6050 sensor to measure acceleration.
   - Displays acceleration data on the OLED screen.

3. **Vibration Alerts:**
   - Triggers vibration alerts when the acceleration exceeds a certain threshold.
   - Vibrates for 1 second in response to sudden changes in acceleration.

4. **LED Indicators:**
   - Changes the color of the NeoPixel LED based on temperature readings.
   - Red for temperatures > 25.0°C, green for 20.0°C < temperature <= 25.0°C, and blue for temperatures <= 20.0°C.
   - Implements a basic low-pass filter for temperature data.

5. **Humidity Alert:**
   - Blinks a purple light on the NeoPixel if humidity exceeds 39.0%.
   - Turns off after 20 seconds.

6. **User Interaction:**
   - Displays a welcome message on the OLED screen upon startup.

## Setup Instructions

1. **Hardware Setup:**
   - Connect the BME280 and MPU6050 sensors to the SAMD21 QT Py via the I2C bus.
   - Connect the NeoPixel LED and vibrator to the specified pins.

2. **Software Setup:**
   - Install the required libraries using the Arduino IDE or your preferred platform.
   - Upload the provided Arduino code to the SAMD21 QT Py.

3. **Calibration:**
   - Adjust the offsets in the code to calibrate the sensors according to the user's height and position.

4. **Run the Device:**
   - Power on the wearable device.
   - Observe sensor data on the OLED display, LED color changes, and vibration alerts.

## Dependencies

- Adafruit Sensor Library
- Adafruit BME280 Library
- Adafruit MPU6050 Library
- Adafruit GFX Library
- Adafruit SSD1306 Library
- Adafruit NeoPixel Library

## Contributing

Contributions are welcome! If you find issues or have suggestions for improvements, please open an issue or create a pull request.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use and modify the code as needed.
