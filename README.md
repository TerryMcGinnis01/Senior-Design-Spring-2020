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
LabVIEW checks the buffer for a "ready to receive" byte from Arduino.  When received, LabVIEW sends a string containing a confirmation byte, motor positions, and on/off for each relay.

The string sent from LabVIEW breaks down as follows:
- a confirmation "!" character
- 5 digit integers for each motor #1-10, with left padding of any needed 0's.
- a single 0 or 1 for all circulation fans.
- a 0 or 1 for each relay.

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

### How the Arduino Code Works:

The Arduino code scans through the 8 channels of the multiplexer, and if there is data it will write to the buffer 2 bytes as an identifier followed by the data itself.
