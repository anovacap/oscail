#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3);        // Initialize UNO RX2 | TX3 connect to combined TX | RX of HC05s

#define STEPPER_PIN_1 9               // Setup UNO pin9 for stepper motor orange
#define STEPPER_PIN_2 10              // Setup UNO pin10 for stepper motor green
#define STEPPER_PIN_3 11              // Setup UNO pin11 for stepper motor yellow
#define STEPPER_PIN_4 12              // Setup UNO pin12 for stepper motor brown

int step_number = 0;                  // Used for opperating the 4 pins
const byte BTpin = 7;                 // From State pin HC05 to UNO pin7 white
const byte BT2pin = 5;                // From State pin HC05_2 to UNO pin5 white
int toWifi = 8;                       // Signal to WiFi Bluetooth white
int toWifi2 = 13;                     // Signal to WiFi Bluetooth white
int openStatus = 6;                   // Open state of UNO

void setup() {
    pinMode(STEPPER_PIN_1, OUTPUT);   // Initialize pin9 UNO - stepper motor IN4 orange
    pinMode(STEPPER_PIN_2, OUTPUT);   // Initialize pin10 UNO - stepper motor IN3 green
    pinMode(STEPPER_PIN_3, OUTPUT);   // Initialize pin11 on UNO - stepper motor IN2 yellow
    pinMode(STEPPER_PIN_4, OUTPUT);   // Initialize pin12 on UNO - stepper motor IN1 brown
    pinMode(BTpin, INPUT);            // Initialize pin7 on UNO
    pinMode(BT2pin, INPUT);           // Initialize pin5 on UNO
    pinMode(toWifi, OUTPUT);          // Initialize pin8 on UNO
    pinMode(toWifi2, OUTPUT);         // Initialize pin13 on UNO
    pinMode(openStatus, OUTPUT);      // Initialize pin6 on UNO output to Wifi 
    BTserial.begin(9600);             // Default communication rate of bluetooth connector
    Serial.begin(115200);             // Hardware serial for USB
    Serial.println("Hello");          // "Hello" output through serial port 
}


void loop() {
    int rec = 0;                      // BT message
    int a = 0;                        // for loop itt
    int i = 0;                        // for loop itt
    int b = 0;                        // place holder for door position
    String fromPC = "";               // Stores characters sent from APP
                                      // look for command in rest mode logic
    digitalWrite(openStatus, HIGH);
    rec = 0;
    if(BTserial.available() > 0) {    // checks if connection to bluetooth
        rec = BTserial.read();        // reads data from bluetooth
        Serial.print((char)BTserial.read()); // send it to the PC
    }
    if (Serial.available()) {
        delay(10);
        fromPC = (char)Serial.read();
        BTserial.print(fromPC);
        Serial.print(fromPC);
    }
    if ( digitalRead(BTpin)==HIGH){   // Tests whether hc05 is connected
        digitalWrite(toWifi, HIGH);
    }
    else {
        digitalWrite(toWifi, LOW);
    }
    if ( digitalRead(BT2pin)==HIGH){  // Tests whether hc05_2 is connected
        digitalWrite(toWifi2, HIGH);
    }
    else {
        digitalWrite(toWifi2, LOW);
    }
    if (rec == 'a') {
        digitalWrite(openStatus, LOW);
        b = 0;
    begin_open:                       // Label for open loop 
        rec = 0;
        for(i = b; i < 600; i++) {    // OPEN loop
            OneStep(true);            // Calls open loop
            delay(2);
        }
    dela:                             // dela label 
        rec = 0;
        delay(3000);                  // the delay in door loop befor close after open
        // Dela postion listen logic
        if(BTserial.available() > 0) { // checks if connection to bluetooth
            rec = BTserial.read();    // reads data from bluetooth
        }
        if(rec == 'a') {
            goto dela;
        }    
        rec = 0;    
        for(a = 600; a > 0; a--){   // CLOSE loop
                                    // Closing postion listen loop
            OneStep(false);
            delay(10);
            if(BTserial.available() > 0) { // checks if connection to bluetooth
                rec = BTserial.read(); // reads data from bluetooth
            }
            if(rec == 'a') {          // If 'a' is received again open again
                b = a;
                goto begin_open;
            }    
        }
        digitalWrite(openStatus, HIGH);
        rec = 0;
    }
}
                                   // Below code controls the stepper motor
void OneStep(bool dir) {           //Declares rotation direction
    if(dir) {
        switch(step_number) {
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
    } else {
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
    if(step_number > 3) {
        step_number = 0;
    }
}
