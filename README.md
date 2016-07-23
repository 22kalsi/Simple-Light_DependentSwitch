# Water-Level-Sensor
Sensing the water level in your tank with arduino+HC-04

List of components :-
Arduino UNO/NANO
HC-04 Ultra Sonic Sensor
Wires
LCD 16x4 charaxters(16x2 character lcd will also do work, But code have to change accordingly.)

Library used :-
Bargraph - http://playground.arduino.cc/Code/LcdBarGraph
NewPing  - http://playground.arduino.cc/Code/NewPing

Pin configuratioons :-
LCD   - * LCD RS pin to digital pin 7
        LCD Enable pin to digital pin 6
        LCD D4 pin to digital pin 5
        LCD D5 pin to digital pin 4
        LCD D6 pin to digital pin 3
        LCD D7 pin to digital pin 2
        LCD R/W pin to ground
        LCD VSS pin to ground
        LCD VCC pin to 5V
        10K resistor:
        ends to +5V and ground
        wiper to LCD VO pin (pin 3)
HC-04 - TRIGGER_PIN  12  
        ECHO_PIN     11  
