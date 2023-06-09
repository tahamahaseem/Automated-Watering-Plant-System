# Automated-Watering-Plant-System

Arduino-based water plant system automates indoor plant care. Monitors temperature, humidity, watering, and light for optimal growth. User-friendly programming with Arduino Uno R3. Affordable and practical solution for hassle-free plant maintenance. 

## Repository Structure

The repository is structured as follows:

- `ProjectCode.ino`: This is the main Arduino sketch file that contains the final code for the water plant system. It integrates all the sub-portions of the system.
- 
Other folders include:

- `Humidity_Sensor`: This folder contains the code for the humidity sensor. It has its own `Humidity_Sensor.ino` file that controls the functionality of the humidity sensor.
- `Moisture_Sensor`: This folder contains the code for the moisture sensor. It has its own `Moisture_Sensor.ino` file that controls the functionality of the moisture sensor.
- `RTC`: This folder contains the code for the Real-Time Clock (RTC) module. It has its own `RTC.ino` file that controls the functionality of the RTC.
- `Bluetooth`: This folder contains the code for the Bluetooth module. It has its own `Bluetooth.ino` file that controls the functionality of the Bluetooth module.
- `ds3231_RTC`: This folder contains the code for the DS3231 RTC module. It has its own `ds3231_RTC.ino` file that controls the functionality of the DS3231 RTC module.


## Arduino Setup

Follow these steps to set up the system:

1. Connect the Arduino board to your computer.
2. Open the `ProjectCode.ino` file in the Arduino IDE.
3. Upload the code to the Arduino board.
4. Connect all sensors and actuators to the correct pins using the schematics provided on the Arduino board. (https://github.com/tahamahaseem/Automated-Watering-Plant-System/blob/main/README.md#libraries)
5. Make sure all the required libraries provided are installed for the respective sensors, actuators, and modules. (https://github.com/tahamahaseem/Automated-Watering-Plant-System/blob/main/README.md#libraries)
6. Power on the Arduino board.
7. The system is now ready to use.

## System Overview

The Water Plant System consists of several sensors and actuators that work together to ensure optimal plant care. The system includes the following components:

- LCD Display: Shows data from different sensors.
- Sensors:
  - Photoresistor: Measures light levels.
  - Pushbutton: Switches between different data displayed on the LCD.
  - Water level sensor: Detects the water level in the tank.
  - Temperature and humidity sensor: Measures the ambient temperature and humidity.
  - Capacitive soil moisture sensor: Measures soil moisture levels.
  - DS3231 RTC Module: Provides real-time clock functionality.
- Actuators:
  - Water DC pump: Supplies water to the plants.
  - Buzzer: Produces audible alerts.
  - DC fan: Controls air circulation and humidity.
  - Servo motor vent: Controls ventilation.
  - 8x8 LED matrix: Provides plant growth lighting.

## System Usage

1. Power on the Water Plant System by connecting it to a power source.

2. The LCD Display will show the current data page

3. To switch between different data pages on the LCD Display, press and release the pushbutton. Each press will cycle to the next data page.

4. The available data pages on the LCD Display are:
   - Temperature and humidity levels
   - Water levels in the tank
   - Light levels
   - Soil moisture levels
   - Time since the plants were last watered

5. To obtain accurate readings, ensure that all sensors are properly connected and positioned.

6. The water pump operates based on the water level and soil moisture readings:
   - If the water levels in the tank are low or empty, the water pump will be temporarily turned off until the tank is filled to a reasonable range.
   - If the soil moisture levels are below 20%, indicating dry soil, the water pump will be activated to water the plants. This only occurs if there is water in the tank.

7. The system relies on the DS3231 RTC Module for timing and control. The RTC is used as a cooldown mechanism for the water pump. After each pump activation (1500 milliseconds), the RTC time is reset and waits for a minute to elapse before the pump can be activated again if necessary. This ensures controlled watering intervals.

8. The DC fan and servo motor vent help maintain appropriate humidity and temperature levels in the plant's environment. When the humidity levels go above 50% or the temperature exceeds 28 degrees Celsius, both the fan and the vent will activate to reduce moisture and increase airflow.

9. The photoresistor and the 8x8 LED matrix control the plant growth lighting. When the photoresistor senses darkness, the LED matrix will turn on to provide blue and red lights, which are optimal for plant growth. When sufficient or extreme light is detected, the LED matrix will turn off.

## Maintenance

- Ensure that the water tank is regularly filled to an appropriate level to ensure uninterrupted watering.

- Check the soil moisture sensor readings periodically and adjust the watering thresholds if necessary.

- Monitor the functionality of the water pump, fan, and servo motor. If any issues arise, check the connections and troubleshoot accordingly.

- Keep an eye on the water level sensor readings to ensure its accuracy. If inconsistent readings occur, consider replacing the sensor.

- Verify the functionality of the humidity and temperature sensor to ensure accurate environmental control. If unusual readings are observed, check the sensor and replace it if necessary.

## Troubleshooting
If you encounter any issues with the Water Plant System, consider the following troubleshooting steps:

1. Check the power supply and connections to ensure everything is properly connected.

2. Verify that all sensors and actuators are correctly connected and positioned.

3. Ensure that the code is correctly uploaded to the microcontroller and check for any error messages.

4. Inspect the system components for any visible damage or loose connections.

## Resources 

### Sensors and Actuators

To use this water plant system, you will need the following components:

- 1 12V Water Pump	
- 1 LED Matrix	
- 1 DC Fan	
- 1 HC-06 Bluetooth	 	
- 1 LCD screen
- 1 PCF8574t	
- 3 Resistors (1K)	 
- 1 Push button	 
- 2 DC relay	 
- 1 Photoresistor	 
- 1 DHT (temperature and humidity sensor)	 
- 1 Water Level Sensor	
- 1 Capacitive Soil Moisture Sensor	
- F-F jumper cable packs	
- 1 tubing
- 1 DS3231 RTC I2C 

### Libraries

- `RTClib.h`: Used for RTC module
- `LiquidCrystal_I2C.h`: Used for	LCD and I2C Communication
- `dht.h`: Used for	Humidity and Temperature Sensor
- `FastLED.h`: Used for	8X8 LED Matrix
- `Servo.h`: Used for	Servo Motor

## Design

### Arduino Pin Layout
![image](https://github.com/tahamahaseem/Automated-Watering-Plant-System/assets/52297139/6998d298-6d96-406d-b413-7af2745bccdf)

### PCB Design
![image](https://github.com/tahamahaseem/Automated-Watering-Plant-System/assets/52297139/763785b9-94e1-4e46-be3b-cbf3bf3afe90)

### Algorithm
![image](https://github.com/tahamahaseem/Automated-Watering-Plant-System/assets/52297139/7fc05b1a-6833-4189-a5db-8bd9f429329e)

### Servo Vent 3D Model
![image](https://github.com/tahamahaseem/Automated-Watering-Plant-System/assets/52297139/0d9a7edf-a9e5-4505-86dc-5b2694c68394)




