#include <ESP8266WiFi.h>// Include the Wi-Fi library
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
#include <SPI.h>

const static char ssid[]     = "drumphsnutz";         // The SSID (name) of the Wi-Fi network you want to connect to
const static char pass[] = "tinyearth720";     // The password of the Wi-Fi network
int status = WL_IDLE_STATUS;
const static char pubkey[] = "pub-c-4392e57b-f7dc-4e1c-a87c-e3cd4f245341";
const static char subkey[] = "sub-c-8575a256-2cd1-11e9-828a-52de7eb65672";
const static char channel[] = "Oscail";
const static char uuid[] = "ArduinoWF";
//const static char auth[] = "1234"


const byte BT2pin = D3;
const byte BT2test = D7;
const byte BTpin = D2;
const byte BTtest =D6;
const byte openStatus = D4;
int errorLED = D1;

int error_flag = 0;
int hello_flag = 0;
int msg_flag = 0;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println("\n");
  PubNub.begin(pubkey, subkey);
  PubNub.set_uuid(uuid);
//  PubNub.set_auth(auth);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

// pin modes
  pinMode(BTtest, INPUT);
  pinMode(BT2test, INPUT);
  pinMode(BTpin, INPUT);
  pinMode(BT2pin, INPUT);
  pinMode(openStatus, INPUT);
  pinMode(errorLED, OUTPUT);

}

void loop() {

  // Hello Message
  if (hello_flag == 0) {
   Serial.println("publishing a message");
   auto client = PubNub.publish(channel, "\{\"text\":\"Welcome to Oscail!\"\}");
   if (!client) {
     Serial.println("publishing error");
     delay(1000);
     return;
   }
   while (client->connected()) {
     while (client->connected() && !client->available());
     char c = client->read();
     Serial.println(c);
   }
   client->stop();
   Serial.println();

   Serial.println("waiting for a messeage (subscribe)");
   PubSubClient *pclient = PubNub.subscribe(channel);
   if (!pclient) {
     Serial.println("subscription error");
     delay(1000);
     return;
   }
   while (pclient->wait_for_data()) {
     char c = pclient->read();
     Serial.print(c);
   }
   pclient->stop();
   Serial.println();
 }
 hello_flag = 1;

 delay(3000);

// Sends Error to PubNub here!!!!!!!
 if (error_flag == 1) {
  if (msg_flag == 0) {
   Serial.println("publishing a message");
    auto client = PubNub.publish(channel, "\{\"text\":\"Critical Error!\"\}");
    if (!client) {
      Serial.println("publishing error");
      delay(1000);
      return;
    }
    while (client->connected()) {
      while (client->connected() && !client->available());
      char c = client->read();
      Serial.println(c);
    }
    client->stop();
    Serial.println();

    Serial.println("waiting for a messeage (subscribe)");
    PubSubClient *pclient = PubNub.subscribe(channel);
    if (!pclient) {
      Serial.println("subscription error");
      delay(1000);
      return;
    }
    while (pclient->wait_for_data()) {
      char c = pclient->read();
      Serial.print(c);
    }
    pclient->stop();
    Serial.println();
    error_flag = 0;
    msg_flag = 1;
  }
 }
 else {
  if (msg_flag == 1) {
   Serial.println("publishing a message");
    auto client = PubNub.publish(channel, "\{\"text\":\"Opperational!\"\}");
     if (!client) {
      Serial.println("publishing error");
      delay(1000);
      return;
    }
    while (client->connected()) {
      while (client->connected() && !client->available());
      char c = client->read();
      Serial.println(c);
    }
    client->stop();
    Serial.println(); 

    Serial.println("waiting for a messeage (subscribe)");
    PubSubClient *pclient = PubNub.subscribe(channel);
    if (!pclient) {
     Serial.println("subscription error");
     delay(1000);
     return;
    }
    while (pclient->wait_for_data()) {
     char c = pclient->read();
     Serial.print(c);
    }
    pclient->stop();
    Serial.println();
    msg_flag = 0;
  }
 }

// Looking for error
 if (digitalRead(openStatus) == HIGH) {  // Checks weather it is open or not
  if ( digitalRead(BTpin)==HIGH){ // Tests weather hc5 is connected
    if (digitalRead(BTtest) == LOW) {
     digitalWrite(errorLED, HIGH);
     error_flag = 1;
    }
    else {
     digitalWrite(errorLED, LOW);
     error_flag = 0;
    }
  }
  else {
    if (digitalRead(BTtest) == HIGH) {
     digitalWrite(errorLED, HIGH);
     error_flag = 1;
    }
    else {
     digitalWrite(errorLED, LOW);
     error_flag = 0;
    }
  }
 

  if ( digitalRead(BT2pin) == HIGH){ // Tests weather hc5 is connected
   if (digitalRead(BT2test) == LOW) {
    digitalWrite(errorLED, HIGH);
    error_flag = 1;
   }
   else {
    digitalWrite(errorLED, LOW);
    error_flag = 0;
   }
  }
  else {
   if (digitalRead(BT2test == HIGH)) {
      digitalWrite(errorLED, HIGH);
      error_flag = 1;
   }
   else {
     digitalWrite(errorLED, LOW);
     error_flag = 0;
   }
  }
 }
 else {
  digitalWrite(errorLED, LOW);
  error_flag = 0;
 }
 
}