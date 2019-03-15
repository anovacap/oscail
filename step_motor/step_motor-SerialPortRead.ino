#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); //RX | TX
//SoftwareSerial BT6serial(4, 5); //RX | TX
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
String fromPC = "";
int step_number = 0;
int rec = 0;
const byte BTpin = 7;
int LED = 6;
boolean BTconnected = false;

void setup() {
pinMode(STEPPER_PIN_1, OUTPUT);
pinMode(STEPPER_PIN_2, OUTPUT);
pinMode(STEPPER_PIN_3, OUTPUT);
pinMode(STEPPER_PIN_4, OUTPUT);
pinMode(BTpin, INPUT);
pinMode(LED, OUTPUT);
BTserial.begin(9600);// Default communication rate of bluetooth connector
Serial.begin(115200); // Harware serial for USB
Serial.println("Hello");
//BT6serial.begin(9600);// Default communication rate of bluetooth
}

void loop() {
 //if (!BTserial.isListening())
 //  BTserial.listen();
 if (BTserial.available() > 0) { // checks if connection to bluetooth
  rec = BTserial.read(); // reads data from bluetooth
  Serial.print((char)BTserial.read()); //send it to the PC
 }
 //if (!BT6serial.isListening())
 //  BT6serial.listen();
 //if (BT6serial.available() > 0) {
 // rec = BT6serial.read(); // read data from buetooth 2
 //}
 if (Serial.available()) {
  delay(10);
  fromPC = (char)Serial.read();
  BTserial.print(fromPC);
  Serial.print(fromPC);
 }
 if ( digitalRead(BTpin)==HIGH){
   digitalWrite(LED, HIGH);
 }
 else {
   digitalWrite(LED, LOW);
 }
 

 if(rec == 'a') {
  for(int a = 0; a < 600; a++){
     OneStep(false);
     delay(2);
  }
  delay(3000);
  for(int a = 0; a < 600; a++){
     OneStep(true);
     delay(10);
  }
  rec = 0;
 }
}


void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
}
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);


}
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}
