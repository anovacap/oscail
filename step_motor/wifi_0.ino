#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char* ssid     = "drumphsnutz";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "tinyearth720";     // The password of the Wi-Fi network
const byte BT2pin = D1;
const byte BT2test = D2;
const byte BTpin = D0;
const byte BTtest =D3;
const byte openStatus = D4;
int ErrorLED = D5;
int count = 0;
int flag_0 = 0;


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
  pinMode(openSatus, INPUT);
  pinMode(ErrorLED, OUTPUT);
}

void loop() {
begin_check:
 delay(1000);
 if (digitalRead(openStatus) == LOW) {  // Checks weather it is open or not
  if ( digitalRead(BTpin)==HIGH){ // Tests weather hc5 is connected
    if (digitalRead(BTtest) == LOW) {
     if (flag_0 == 0) {
      flag_0 = 1;
      goto begin_check;
     }
     digitalWrite(ErrorLED, HIGH);
     flag_0 = 0;
    }
    else {
     digitalWrite(ErrorLED, LOW);
     flag_0 == 0;
    }
  }
  else {
    if (digitalRead(BTtest) == HIGH) {
     if (flag_0 == 0) {
      flag_0 = 1;
      goto begin_check;
     }
     digitalWrite(ErrorLED, HIGH);
     flag_0 = 0;
    }
    else {
     digitalWrite(ErrorLED, LOW);
     flag_0 = 0;
    }
  }


  if ( digitalRead(BT2pin) == HIGH){ // Tests weather hc5 is connected
   if (digitalRead(BT2test) == LOW) {
    if (flag_0 == 0) {
      flag_0 = 1;
      goto begin_check;
    }
    digitalWrite(ErrorLED, HIGH);
    flag_0 = 0;
   }
   else {
    digitalWrite(ErrorLED, LOW);
    flag_0 = 0;
   }
  }
  else {
   digitalWrite(LED2, LOW);
   if (digitalRead(BT2test == HIGH)) {
      if (flag_0 == 0) {
        flag_0 = 1;
        goto begin_check;
      }
      digitalWrite(ErrorLED, HIGH);
      flag_0 = 0;
   }
   else {
     digitalWrite(ErrorLED, LOW);
     flag0 = 0;
   }
  }
 }
  
}