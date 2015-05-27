# OPTIMUS_BLIND_SPOT_DETECTOR 

Arduino library integrating SR04 &amp; NewPing with HC-05 Bluetooth

This is the code for my capstone project. 
Using inexpensive ultrasonic sensors, Bluetooth modules and Arduinios, 
my group designed an affordable blind spot detector that provides audible warnings and an led display to alert drivers of hidden obstacles.

Our program utilizes Tim Eckel's NewPing library (http://playground.arduino.cc/Code/NewPing) and his NewTone library
to efficiently measure distances with the SR04 ultrasonic sensor. Data from the sensors is concatenated and transmitted through the Bluetooth
connection with SoftwareSerial which is then displayed on the TM1638 7-segment led display. Control of the TM1638 is accomplished thanks
to Ricardo Batista's TM1638 library (http://code.google.com/p/tm1638-library/)
