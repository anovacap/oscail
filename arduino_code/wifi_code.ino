#include <ESP8266WiFi.h>                        // Include the Wi-Fi library
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
#include <SPI.h>

const byte BT2pin = D3;                         // Bluetooth_2 status from arduino
const byte BT2test = D7;                        // Bluetooth_2 status from actual bluetooth module
const byte BTpin = D2;                          // Bluetooth status from arduino
const byte BTtest =D6;                          // Bluetooth status from actual bluetooth module 
const byte openStatus = D4;                     // Tells when door is opening 
int errorLED = D1;                              // Out to LED light on Breadboard
int welcome_flag = 0;                           // 0 if client instace success. 1 after succeeds

void setup() {
    const static char ssid[]     = "XXXX";      // The SSID (name) of the Wi-Fi network you want to connect to
    const static char pass[] = "XXXXXXX";       // The password of the Wi-Fi network
    const static char uuid[] = "ArduinoWF";     // PN Wifi name on channel
    const static char pubkey[] = "DEMO";        // Add your personal PN pubkey
    const static char subkey[] = "DEMO";        // Add your personal PN subkey
    Serial.begin(115200);                       // Start the Serial communication to send messages serial monitor
    delay(10);
    Serial.println("\n");                       // Message to serial monitor
    PubNub.begin(pubkey, subkey);               // Instantiate a PubNub instance
    PubNub.set_uuid(uuid);                      // Create the UUID for the device
    WiFi.begin(ssid, pass);                     // Connect to Wifi
    Serial.print("Connecting to ");             // Message to serial monitor
    Serial.print(ssid); Serial.println(" ..."); // Message to serial monitor
    Serial.println('\n');                       // Message to serial monitor
    Serial.println("Connection established!");  // Message to serial monitor
    Serial.print("IP address:\t");              // Message to serial monitor
    Serial.println(WiFi.localIP());             // Send the IP address of the ESP8266 to the computer
    // pin modes
    pinMode(BTtest, INPUT);                     // Initialize pin6 as input
    pinMode(BT2test, INPUT);                    // Initialize pin7 as input
    pinMode(BTpin, INPUT);                      // Initialize pin2 as input
    pinMode(BT2pin, INPUT);                     // Initialize pin3 as input
    pinMode(openStatus, INPUT);                 // Initialize pin4 as input
    pinMode(errorLED, OUTPUT);                  // Initialize pin1 as input
}

void loop() {                                   // Welcome message published to APP                                             
    int error_flag;
    int msg_flag;
    const static char channel[] = "Oscail";     // PN channel
    if (welcome_flag == 0) {                    // Welcome message displayed when client instantiated
        int status = WL_IDLE_STATUS;
        error_flag = 0;                         // 1 if error. 0 if no error
        msg_flag = 0;                           // 0 to proceed with message. 1 to stop (error part of code)
        Serial.println("publishing a message"); // Out to serial monitor
        auto client = PubNub.publish(channel, "\{\"text\":\"Welcome to Oscail!\"\}"); // Out to APP
        if (!client) {
            Serial.println("publishing error"); // Out to serial monitor
            delay(1000);
            return;
        }                                   
        while (client->connected()) {           // Client message published to serial monitor
            while (client->connected() && !client->available());{
                char c = client->read();
                Serial.println(c);              // To PC
            }
        }
        client->stop();
        Serial.println();                                             
        Serial.println("waiting for a message (subscribe)");
        PubSubClient *pclient = PubNub.subscribe(channel);// Subscribe setup for future messages - updates?
        if (!pclient) {
            Serial.println("subscription error");
            delay(1000);
            return;
        }          
        while (pclient->wait_for_data()) {      // Subscribe message read to serial monitor (not used yet)
            char c = pclient->read();
            Serial.print(c);
        }
        pclient->stop();
        Serial.println();
    }
    welcome_flag = 1;                           // Stop welcome message client instance
    delay(3000);                                          
    if (error_flag == 1) {                      // Publish Error to PubNub if Aruduino UNO is down
        if (msg_flag == 0) {
            Serial.println("publishing a message");// To PC
            auto client = PubNub.publish(channel, "\{\"text\":\"Critical Error!\"\}"); // To App
            if (!client) {
                Serial.println("publishing error"); // To PC
                delay(1000);
                return;
            }                        
            while (client->connected()) {       // Read client message out to serial monitor
                while (client->connected() && !client->available());{
                    char c = client->read();
                    Serial.println(c);
                }
            }
            client->stop();
            Serial.println();                             
            Serial.println("waiting for a message (subscribe)");// Subscribe for future use
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
    if (msg_flag == 1) {                        // Publish Operational! when UNO is good 
        Serial.println("publishing a message"); // To PC
        auto client = PubNub.publish(channel, "\{\"text\":\"Operational!\"\}"); // To App
        if (!client) {
            Serial.println("publishing error"); // To PC
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
        Serial.println("waiting for a messeage (subscribe)");// Setup for future subscribed messages handling
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
    if (digitalRead(openStatus) == HIGH) {       // Checks whether it is open or not
        if ( digitalRead(BTpin)==HIGH){          // Tests whether hc05 is connected
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
                                                 // Tests for hc05 not used
        if ( digitalRead(BT2pin) == HIGH){       // Tests whether hc05 is connected
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