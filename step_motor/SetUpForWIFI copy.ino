
#include <ESP8266WiFi.h>// Include the Wi-Fi library
#define PubNub_BASE_CLIENT WiFiClient
#include <PubNub.h>
#include <SPI.h>

const static char ssid[]     = "drumphsnutz";         // The SSID (name) of the Wi-Fi network you want to connect to
const static char pass[] = "tinyearth720";     // The password of the Wi-Fi network
int status = WL_IDLE_STATUS;
const static char pubkey[] = "pub-c-4392e57b-f7dc-4e1c-a87c-e3cd4f245341";
const static char subkey[] = "sub-c-8575a256-2cd1-11e9-828a-52de7eb65672";
const static char channel[] = "Channel-Oscail";
const static char uuid[] = "ArduinoWF";
//const static char auth[] = "1234"
void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
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
}

void loop() {
  Serial.println("publishing a message");
  auto client = PubNub.publish(channel, "\"\\\"Hello world!\\\" from Arduino.\"");
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
