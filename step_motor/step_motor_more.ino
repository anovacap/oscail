#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); //RX | TX

#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

String fromPC = "";
int step_number = 0;
int rec = 0;
const byte BTpin = 7;
int LED = 6;
int a = 0;
int i = 0;
int b = 0;
boolean BTconnected = false;
boolean BT6connected = false;

void setup() {
//Serial.begin(9600);
pinMode(STEPPER_PIN_1, OUTPUT);
pinMode(STEPPER_PIN_2, OUTPUT);
pinMode(STEPPER_PIN_3, OUTPUT);
pinMode(STEPPER_PIN_4, OUTPUT);
pinMode(BTpin, INPUT);
pinMode(LED, OUTPUT);
BTserial.begin(9600); // Default communication rate of bluetooth connector
Serial.begin(115200); // Harware serial for USB
Serial.println("Hello");
//BT6serial.begin(9600);
}


void loop() {
  // look for command in rest mode logic
 rec = 0;
 if(BTserial.available() > 0) { // checks if connection to bluetooth
  rec = BTserial.read(); // reads data from bluetooth
  Serial.print((char)BTserial.read()); //send it to the PC
  }

 if (Serial.available()) {
  delay(10);
  fromPC = (char)Serial.read();
  BTserial.print(fromPC);
  Serial.print(fromPC);
 }

 if ( digitalRead(BTpin)==HIGH){ // Tests weather hc5 is connected
   digitalWrite(LED, HIGH);
 }
 else {
   digitalWrite(LED, LOW);
 }

 if(rec == 'a') {
  b = 0;
begin_open:
  rec = 0;
  for(i = b; i < 600; i++){ //OPEN loop
     OneStep(false);
     delay(2);
  }
dela: // the delay in door loop befor close after open
  rec = 0;
  delay(3000);
  // Dela postion listen logic
  if(BTserial.available() > 0) { // checks if connection to bluetooth
   rec = BTserial.read(); // reads data from bluetooth
  }
  if(rec == 'a') {
    goto dela;
  }
  
  rec = 0;
  
  for(a = 600; a > 0; a--){ //CLOSE loop
     // Closing postion listen lop

   OneStep(true);
   delay(10);
   if(BTserial.available() > 0) { // checks if connection to bluetooth
    rec = BTserial.read(); // reads data from bluetooth
   }
   if(rec == 'a') {
    b = a;
    goto begin_open;
   }
   
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