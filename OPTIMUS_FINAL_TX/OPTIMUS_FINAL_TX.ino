//OPTIMUS Blind Spot Detection System Source Code 2.0 - Master Version
//April 7th, 2015
//By Alex, Arvind, Akash and David

#include <NewPing.h> //calls the library that controlls the sonar sensors
#include <SoftwareSerial.h> //bluetooth serial library

SoftwareSerial mySerial(A3, A4); //RX, TX Define the serial data pins

#define TRIG1  13  //Define the pins for the the 7 sensors
#define ECHO1  12 
#define TRIG2  11  
#define ECHO2  10
#define TRIG3 9
#define ECHO3 8
#define TRIG12  7  
#define ECHO12  6  
#define TRIG22  5  
#define ECHO22  4
#define TRIG32 3
#define ECHO32 2
#define TRIGR A0 //Reverse Sensor
#define ECHOR A1
#define MAX_DISTANCE 300 //Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define BlinkL A4 //Left and right turn signals. CANBUS connectivity is possible but was not completed. 
#define BlinkR A5

//Creates the sonar objects and defines the pins
NewPing sonarL1(TRIG1, ECHO1, MAX_DISTANCE); //NewPing setup of pins and maximum distance.
NewPing sonarM1(TRIG2, ECHO2, MAX_DISTANCE); 
NewPing sonarR1(TRIG3, ECHO3, MAX_DISTANCE); 
NewPing sonarR(TRIGR, ECHOR, 100); //Reverse sensor
NewPing sonarL2(TRIG12, ECHO12, MAX_DISTANCE); 
NewPing sonarM2(TRIG22, ECHO22, MAX_DISTANCE); 
NewPing sonarR2(TRIG32, ECHO32, MAX_DISTANCE); 


void setup(){
  Serial.begin(9600); //Serial console for debugging
  Serial.println("Begin");
  mySerial.begin(38400); //Starts the bluetooth serial connection
  pinMode(BlinkL, INPUT);
  pinMode(BlinkR, INPUT);
}

void loop() {
  String data = ""; //Placeholder for the data to be transmitted
  String BL = ""; //Placeholder for the turn signal data
  String BR = "";
  delay(30);
  String cm1 = String(sonarL1.convert_cm(sonarL1.ping())); //pings each sensor in a specific 
  String cm2 = String(sonarL1.convert_cm(sonarL2.ping())); //pattern so as to minimize echo
  String cmR = String(sonarL1.convert_cm(sonarR.ping()));
  delay(30);
  String cm3 = String(sonarL1.convert_cm(sonarM1.ping())); //then converts each distance in cm to a string
  String cm4 = String(sonarL1.convert_cm(sonarM2.ping())); //to simplify the transmission
  delay(30);
  String cm5 = String(sonarL1.convert_cm(sonarR1.ping()));
  String cm6 = String(sonarL1.convert_cm(sonarR2.ping()));
  
  if(analogRead(BlinkL)>10){BL = "1";} //Workaround solution for lack of CANBUS connectivity. Turn signal lamp voltage is measured through a splice to detect activity. 
  else{BL = "0")
  if(analogRead(BlinkR)>10){BR = "1";}
  else(BR = "0";)
  
  data = cm1 + cm3 + cm5 + cm2 + cm4 + cm6 + cmR + BL + BR; //combines the measured distances into a single string
  
  Serial.println(data); //prints to serial console for debugging
  if(mySerial.available()){ //ensures theres a BT connection
    if(mySerial.read()=='R'){ //Waits for the master to be ready
      mySerial.write(data);}} //Sends the distances to the master
}



