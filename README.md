# Ezlo - Thermostat
Ezlo Thermostat is an enhanced version of the Centralite Thermostat product that gives user the exciting feature of a smart thermostat system accompanied by the amazing MiOS dashboard in a tablet screen on the thermostat product that greatly adds to the overall experience and UI.
The thermostat is accompanied by a separate small PCB that mounts the infineon Radar sensor for presence and occupancy sensing.

## Project Requirements v2.0
The schematic design was already finished and tested to run successfully with the existing features. The new version will have the following features in addition to existing features both of which are listed below:
* The thermostat should be based off of and ESP32-S3 based module.
* The thermostat should have a separate PCB that mounts the Infineon Radar sensor.
* The thermostat will have 2 x cameras. The datasheet of the cameras are attached. [HK-2385^M2385-706(7731)  Camera Spec 承认书.pdf](https://github.com/eSpark-Consultants/ezlo-thermostat/files/11762271/HK-2385.M2385-706.7731.Camera.Spec.pdf). According to client, the cameras are intended to be connected directly with the tablet but a thorough study of the attached camera module is necessary to confirm this. There will be 2 x camera modules used in thermostat design.
* The thermostat will have an android 7" tablet for displaying the MiOS dashboard. The tablet datasheet is attached.[LCD Display Spec 7inch.pdf](https://github.com/eSpark-Consultants/ezlo-thermostat/files/11762286/LCD.Display.Spec.7inch.pdf). Attached further are the dxf drawings of the LCD (not confirmed. [F0753_V1.1-2D(1) PCB.zip](https://github.com/eSpark-Consultants/ezlo-thermostat/files/11762290/F0753_V1.1-2D.1.PCB.zip)
* The thermostat will have basic amplitude detection using 1 or 2 microphones (as suitable)
* The thermostat will have gesture recognition capability. A module is suggested by client which is **GY- PAJ7620U2** but open to better options. The selection should prioritize cost effectiveness and available firmware support. 
* Another point of discussion is if the internet / WiFi goes down, what is the most feasible means of communication between Tablet and on board ESP32? A few options are; ESP32 as Web Server; BLE; Wired link between tablet and ESP32.
