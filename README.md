# Documentation

***

Arduino and LabVIEW files designed to allow monitoring and controlling of temperature, CO2 levels, and airflow in a test bed through use of Arduino and DAQ.

***

## Motors, Lights, and Circulation Fans:

### Hardware:

- 1 Arduino Mega 2560 R3
- 10 TB6600 Stepper Motor Drivers
- 10 4-Wire NEMA 17 Stepper Motors
- 4 Relays

### How the vi Works:

![](/Images/SimultaneousControl.png)
LabVIEW checks the buffer for a "ready to receive" signal from Arduino.  When received, LabVIEW sends a confirmation "!" followed by a string about motor positions and on/off of lights and circulation fans.

The string sent breaks down as follows:
- 5 digit integers for each motors
- a single 0 or 1 for all circulation fans
- a 0 or 1 for each light

### How the Arduino Code Works:



***

## CO2, Temperature, and Humidity Sensing:

### Hardware:

- Arduino Uno
- 8-channel multiplexer
- 6 Grove - CO2 & Temperature & Humidity Sensors for Arduino - SCD30 (https://www.seeedstudio.com/Grove-CO2-Temperature-Humidity-Sensor-SCD30-p-2911.html)

### How the vi Works:
![](/Images/co2Readings.png)
LabVIEW checks the buffer for incoming bytes.  The first 2 bytes received determines what measurement it is receiving (ex. t5 means temperature reading from sensor 5).  It displays each reading in a separate indicator.  The data is appended to a plain text file.

### Arduino code:
