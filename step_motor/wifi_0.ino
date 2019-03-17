#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char* ssid     = "drumphsnutz";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "tinyearth720";     // The password of the Wi-Fi network
const byte BT2pin = D1;
const byte BT2test = D4;
const byte BTpin = D0;
const byte BTtest =D5;
int LED = D2;
int LED2 = D3;
int ErrorLED = D6;
int count = 0;


void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

  pinMode(BTtest, INPUT);
  pinMode(BT2test, INPUT);
  pinMode(BTpin, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BT2pin, INPUT);
  pinMode(LED2, OUTPUT);
  pinMode(ErrorLED, OUTPUT);
}

void loop() {
 if (count == 0) {
  digitalWrite(LED, LOW);
  digitalWrite(LED2, LOW);
 }
 if ( digitalRead(BTpin)==HIGH){ // Tests weather hc5 is connected
   digitalWrite(LED, HIGH);
   if (digitalRead(BTtest) == LOW) {
    digitalWrite(ErrorLED, HIGH);
   }
   else {
    digitalWrite(ErrorLED, LOW);
   }
 }
 else {
   digitalWrite(LED, LOW);
   if (digitalRead(BTtest) == HIGH) {
    digitalWrite(ErrorLED, HIGH);
   }
   else {
    digitalWrite(ErrorLED, LOW);
   }
 }


 if ( digitalRead(BT2pin)==HIGH){ // Tests weather hc5 is connected
   digitalWrite(LED2, HIGH);
   if (digitalRead(BT2test) == LOW) {
    digitalWrite(ErrorLED, HIGH);
   }
   else {
    digitalWrite(ErrorLED, LOW);
    
   }
 }
 else {
   digitalWrite(LED2, LOW);
   if (digitalRead(BTtest == HIGH)) {
      digitalWrite(ErrorLED, HIGH);
    }
    else {
      digitalWrite(ErrorLED, LOW);
    }
 }
 count++;
  
}