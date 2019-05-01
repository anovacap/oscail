#include <ESP8266WiFi.h>// Include the Wi-Fi library
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
#include <SPI.h>

const static char ssid[]     = "XXXX";         // The SSID (name) of the Wi-Fi network you want to connect to
const static char pass[] = "XXXXXXX";     // The password of the Wi-Fi network
int status = WL_IDLE_STATUS;
const static char pubkey[] = "DEMO"; // Add your personal PN pubkey
const static char subkey[] = "DEMO"; // Add your personal PN subkey
const static char channel[] = "Oscail"; // PN channel
const static char uuid[] = "ArduinoWF"; //PN Wifi name on channel

const byte BT2pin = D3; //
const byte BT2test = D7;
const byte BTpin = D2;
const byte BTtest =D6;
const byte openStatus = D4; 
int errorLED = D1; // Out to LED light on Breadboard

int welcome_flag = 0; // 0 if client instace success. 1 after succeeds
int error_flag = 0; // 1 if error. 0 if no error
int msg_flag = 0; // 0 to proceed with message. 1 to stop (error part of code)

void setup() {
    Serial.begin(115200);         // Start the Serial communication to send messages serial monitor
    delay(10);
    Serial.println("\n");         // Message to serial monitor
    PubNub.begin(pubkey, subkey); // Instantiate a PubNub instance
    PubNub.set_uuid(uuid);        // Create the UUID for the device
    WiFi.begin(ssid, pass);       // Connect to Wifi
    Serial.print("Connecting to ");             // Message to serial monitor
    Serial.print(ssid); Serial.println(" ..."); // Message to serial monitor
    Serial.println('\n');                       // Message to serial monitor
    Serial.println("Connection established!");  // Message to serial monitor
    Serial.print("IP address:\t");              // Message to serial monitor
    Serial.println(WiFi.localIP());             // Send the IP address of the ESP8266 to the computer

    // pin modes
    pinMode(BTtest, INPUT); // Initialize pin6 as input
    pinMode(BT2test, INPUT); // Initialize pin7 as input
    pinMode(BTpin, INPUT);   // Initialize pin2 as input
    pinMode(BT2pin, INPUT);  // Initialize pin3 as input
    pinMode(openStatus, INPUT); // Initialize pin4 as input
    pinMode(errorLED, OUTPUT);  // Initialize pin1 as input
}

void loop() {
  // Welcome message published to APP 
    if (welcome_flag == 0) { // Welcome message displayed when client instantiated
        Serial.println("publishing a message"); // Out to serial monitor
        auto client = PubNub.publish(channel, "\{\"text\":\"Welcome to Oscail!\"\}"); // Out to APP
        if (!client) {
            Serial.println("publishing error"); // Out to serial monitor
            delay(1000);
            return;
        }
        // client message published to serial monitor
        while (client->connected()) {
            while (client->connected() && !client->available());{
                char c = client->read();
                Serial.println(c);
            }
        }
        client->stop();
        Serial.println();
        // Subscribe setup for future messages - updates?
        Serial.println("waiting for a messeage (subscribe)");
        PubSubClient *pclient = PubNub.subscribe(channel);
        if (!pclient) {
            Serial.println("subscription error");
            delay(1000);
            return;
        }
        // Subscribe message read to serial monitor (not used yet)
        while (pclient->wait_for_data()) {
            char c = pclient->read();
            Serial.print(c);
        }
        pclient->stop();
        Serial.println();
    }
    welcome_flag = 1; // Stop welcome message client instance

    delay(3000);

// Publish Error to PubNub if Aruduino UNO is down
    if (error_flag == 1) {
        if (msg_flag == 0) {
            Serial.println("publishing a message");
            auto client = PubNub.publish(channel, "\{\"text\":\"Critical Error!\"\}");
            if (!client) {
                Serial.println("publishing error");
                delay(1000);
                return;
            }
            // Read client message out to serial monitor
            while (client->connected()) {
                while (client->connected() && !client->available());{
                    char c = client->read();
                    Serial.println(c);
                }
            }
            client->stop();
            Serial.println();
            // Subscribe for future use
            Serial.println("waiting for a message (subscribe)");
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
    if (msg_flag == 1) { // Publish Opperational! when UNO is good 
        Serial.println("publishing a message");
        auto client = PubNub.publish(channel, "\{\"text\":\"Opperational!\"\}");
        if (!client) {
            Serial.println("publishing error");
            delay(1000);
            return;
        }
        while (client->connected()) {
            while (client->connected() && !client->available());{
                char c = client->read();
                Serial.println(c);
            }
        }
        client->stop();
        Serial.println(); 
        // Setup for future subscribed messages handling
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
    if (digitalRead(openStatus) == HIGH) {  // Checks whether it is open or not
        if ( digitalRead(BTpin)==HIGH){ // Tests whether HC05 is connected
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

        // Tests for HC05s not used
        if ( digitalRead(BT2pin) == HIGH){ // Tests whether hc5 is connected
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