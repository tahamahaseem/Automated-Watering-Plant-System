# Automated-Watering-Plant-System

Arduino-based water plant system automates indoor plant care. Monitors temperature, humidity, watering, and light for optimal growth. User-friendly programming with Arduino Uno R3. Affordable and practical solution for hassle-free plant maintenance.

## Project Structure

The repository is structured as follows:

- `ProjectCode.ino`: This is the main Arduino sketch file that contains the final code for the water plant system. It integrates all the sub-portions of the system.
- 
Other folders include:

- `Humidity_Sensor`: This folder contains the code for the humidity sensor. It has its own `Humidity_Sensor.ino` file that controls the functionality of the humidity sensor.
- `Moisture_Sensor`: This folder contains the code for the moisture sensor. It has its own `Moisture_Sensor.ino` file that controls the functionality of the moisture sensor.
- `RTC`: This folder contains the code for the Real-Time Clock (RTC) module. It has its own `RTC.ino` file that controls the functionality of the RTC.
- `Bluetooth`: This folder contains the code for the Bluetooth module. It has its own `Bluetooth.ino` file that controls the functionality of the Bluetooth module.
- `ds3231_RTC`: This folder contains the code for the DS3231 RTC module. It has its own `ds3231_RTC.ino` file that controls the functionality of the DS3231 RTC module.

## Usage

### Sensors and Actuators

To use this water plant system, you will need the following components:

1 12V Water Pump	
1 LED Matrix	
1 DC Fan	
1 HC-06 Bluetooth	 	
1 LCD screen
1 PCF8574t	
3 Resistors (1K)	 
1 Push button	 
2 DC relay	 
1 Photoresistor	 
1 DHT (temperature and humidity sensor)	 
1 Water Level Sensor	
1 Capacitive Soil Moisture Sensor	
F-F jumper cable packs	
1 tubing
Hot hlue gun and sticks
1 DS3231 RTC I2C 

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


Follow these steps to set up the system:

1. Connect the Arduino board to your computer.
2. Open the `ProjectCode.ino` file in the Arduino IDE.
3. Upload the code to the Arduino board.
4. Connect the moisture sensor, humidity sensor, LED 8x8 matrix display, RTC module, Bluetooth module, DS3231 RTC module, and water pump to the appropriate pins on the Arduino board.
5. Make sure all the required libraries are installed for the respective sensors, actuators, and modules.
6. Power on the Arduino board.
7. The system is now ready to use.

The moisture sensor measures the soil moisture levels, the humidity sensor measures the humidity levels, and the LED 8x8 matrix display shows relevant information. The RTC module ensures accurate timekeeping, and the Bluetooth module enables wireless communication. The DS3231 RTC module provides additional real-time clock functionality. When the moisture falls below a certain threshold, the water pump is activated to water the plants. You can customize the code in the `ProjectCode.ino` file and the individual sensor/actuator files to adjust the thresholds or add additional functionality.

