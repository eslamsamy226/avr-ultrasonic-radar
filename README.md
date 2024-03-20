# AVR Ultrasonic Radar
This project is an ultrasonic radar using AVR archticture, where an ultrasonic sensor scans an range of 180 degrees and when it has detected an object it outputs the 
distance and the degree at which it has detected it, the movement of the sensor can be controlled automatically or manualy, one of the challenges I faced in designing
this project is using ATMEGA32's TIMER1 as input captuer unit to interface with the ultrasonic sensor and as signal generator to interface with the servo motor,I managed
to solve this issue by switching between the two peripherals every 20ms. 
 The following components have been used:
 * ATMEGA32 MCU
 * Buzzer
 * Push buttons
 * 2*16 LCD
 * servo motor
 * ultrasonic sensor
 * potentiometer

## 🛠️Drivers
In order to achive the project funtionality I wrote the following drivers:
* DIO
* Buzzer
* LCD
* Push buttons
* Servo 
these drivers can be found in /src forlder

## 👨‍💻Simulation
The proteus simulation design can be found in (radar.pdsprj) file, here is the simulation in action:
https://github.com/eslamsamy226/avr-ultrasonic-radar/assets/128985943/83e5c9ac-c612-433f-b9b5-bd7f9307d2ce

## 🔳Hardware
I have also implemented this project in hardware:


https://github.com/eslamsamy226/avr-ultrasonic-radar/assets/128985943/3fecbf46-14b0-4866-8b19-31a880d3836f





