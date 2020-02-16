This repository contains Arduino and LabVIEW files related to UT Tyler's Mechanical Engineering Senior Design group for Spring 2020.
This project is related to automating equipment for Demand Control Ventilation.

SimultaneousControl Folder:
  Contains Arduino code and LabVIEW vi to control positions of stepper motors through serial communication.  A tb6600 motor driver is used with NEMA 17s.  The input is equal to the number of steps from the motor's starting position.

Seeed-Grove-Sensor Folder:
  Contains Arduino code and LabVIEW vi to read CO2, temperature, and humidity from a single CO2 sensor.  Updates will be made to accomodate reading multiple sensors, and disable the autocalibration function.
