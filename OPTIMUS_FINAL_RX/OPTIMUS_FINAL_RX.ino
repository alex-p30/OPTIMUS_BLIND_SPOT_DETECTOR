//OPTIMUS Blind Spot Detection System Source Code 2.0 - Slave Version
//April 7th, 2015
//By Alex, Arvind, Akash and David

#include <TM1638.h> //control library for the led display
#include <SoftwareSerial.h> //bluetooth serial library
#include <NewTone.h> //improved Tone library for audio warning

#define buzz 6 //speaker pin
#define spd A3 //simulated speed

SoftwareSerial mySerial(10, 11); // RX, TX //bluetooth pins
TM1638 module(8, 9, 7); //create led display object
byte mode; //keeps track of the mode the display is on

int L1; //global variables for the individual distances from the sonar sensors
int M1;
int R1;
   
int L2;
int M2;
int R2;
//123|456|789|123|456|789|!@#|!|!
int R; //distance of the reverse sensor
int BL; //status of the left turn signal
int BR; //status of the right turn signal

int LStatus; //state of detection; 0 is no obstacle, 1 is obstacle with no turn signal, 2  is obstacle with turn signal
int RStatus;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Begin");
  mySerial.begin(38400);
  pinMode(spd, INPUT);
}

void loop() // run over and over
{
  String data = "";
  char temp;
  mySerial.write("R");
  delay(95);
  if(mySerial.available()>0){
     for(int i = mySerial.available(); i > 0; i--){ 
      temp = mySerial.read();
      data.concat(temp);}
      
   Serial.println("Received: " + data);}
   
   L1 = data.substring(0,3).toInt();
   M1 = data.substring(3,6).toInt();
   R1 = data.substring(6,9).toInt();
   
   L2 = data.substring(9,12).toInt();
   M2 = data.substring(12,15).toInt();
   R2 = data.substring(15,18).toInt();
   //123|456|789|123|456|789|!@#|!|!
   R = data.substring(18,21).toInt();
   BL = data.substring(21,22).toInt();
   BR = data.substring(22).toInt();
   
   LStatus = checkL(L1, M1, R1, BL);
   RStatus = checkR(L2, M2, R2, BR);
   
   update();
  }
  
int checkL(unsigned int L1, unsigned int M1, unsigned int R1, unsigned int BL){
  boolean obs = false;
  boolean sig = false;
  int stat = 0;
  if((L1&&M1)>100 && R1 >70){obs = true;}
  if(BL==1){sig = true;}
  if(obs&&sig){stat = 2;}
  else if(obs&&!sig){stat = 1;}
}
  
  
int checkR(unsigned int L2, unsigned int M2, unsigned int R2, unsigned int BR){
  boolean obs = false;
  boolean sig = false;
  int stat = 0;
  if((L2&&M2)>100 && R2 >70){
    obs = true;}
  if(BR==1){
    sig = true;}
  if(obs&&sig){stat = 2;}
  else if(obs&&!sig){stat = 1;}
}
  
void update(){
    byte keys = module.getButtons();
    
    if (keys != 0) {
      mode = (int)keys;
      module.clearDisplay();
      module.setLEDs(0);
      }
      
    switch (mode) {
      case 1:
        module.setLEDs(0xFA00);
        disp1();
        break;
        
      case 2:
        module.setLEDs(0x00AF);
        disp2();
        break;
        
        case 4:
        module.setLEDs(0x0ADB);
        disp4();
        break;
        
        case 8:
        module.setLEDs(0xC9A6);
        disp8();
        break;
    }
}

void disp1(){
  noTone(buzz);
  if((LStatus&&RStatus)==0){module.setDisplayToString("SAFESAFE");}
  if((LStatus==(1||2))){module.setDisplayToString("StOPSAFE");}
  if((RStatus==(1||2))){module.setDisplayToString("SAFEStOP");}
  if((LStatus&&RStatus)==(1||2)){module.setDisplayToString("StOPStOP");}
  if((LStatus||RStatus)==2){if(analogRead(spd)>500){(buzz, 2000);}}
}

void disp2(){
  String L = String((L1+M1)/2); String R = String((L2+M2)/2);
  String disp = L + " " + " " + R;
  module.setDisplayToString(disp, 0, true);
}

void disp4(){
  String L = String(R1); String R = String(R2);
  String disp = L + " " + " " + R;
  module.setDisplayToString(disp, 0, true);
}

void disp8(){
  String Rear = String(R);
  String disp = "rEAr" + Rear;
  module.setDisplayToString(disp, 0, true);
}
