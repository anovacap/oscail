# Oscail
---
## Description
---
* Oscail - Pronounced Uskill - Irish for Open.
* Final Project for Holberton School.
* Create an Android mobile application that allows the user to connect to a door and open it by  pushing a button on the app.
---
<img src="https://github.com/anovacap/oscail/blob/master/IMG_20190319_171913.jpg"  width="250" height="250"> | <img src="https://github.com/anovacap/oscail/blob/master/IMG_20190319_171942.jpg"  width="250" height="250"> |<img src="https://github.com/anovacap/oscail/blob/master/IMG_20190319_171951.jpg"  width="250" height="250"> | <img src="https://github.com/anovacap/oscail/blob/master/IMG_20190319_171954.jpg"  width="250" height="250">
* Create a kit that updates doors to open with the app.
* Ability doors (Handicaped doors) are the intended doors to be upgraded with the kit.
* A wifi component will allow access to door status on line
--- 
## Requirements For APP
1.  App inventor account - Goto http://appinventor.mit.edu/explore/ to create.
2.  Android Device with Bluetooth 4.
3.  Barcode/QR Scanner - Goto Google Play Store.
4.  MIT AI2 Companion - Got Google Play Store.
5.  Change permissions on Android device to allow downloads from unknown sources.
## Requirements For Door
1.  ESP8266 Module ESP-12E NodeMcu LUA WiFi Internet New Version Development Board.
2.  UNO R3 Board ATmega328P ATMEGA16U2.
3.  28BYJ-48 ULN2003 5V Stepper Motor + ULN2003 Driver Board.
4.  HC 05 Bluetooth Module.
5.  Breadboard.
6.  Resistors = 1 330ohm, 1 1kohm, 1 2.2kohm.
7.  1 led.
8.  Male to male jumper cables
9.  Wood, nail, screws, paint
10. Aruino Create https://www.arduino.cc/en/main/software
11. PubNub Arduino SDK https://www.pubnub.com/docs/arduino/pubnub-arduino-sdk
## Instructions
1.  Go to  http://appinventor.mit.edu/explore/ - You will need a QR reader from Google Play Store.
2.  Select "Create apps!" in upper left corner. Sign up or login.
3.  Goto "Projects" menu. Select "Import project (.aia) from my computer ..."
4.  Navigate in chooser to oscail/App_inventor/OSCAIL_1.aia - Project will load in App inventor browser.
5.  Goto "Build" menu. Select "App (provide QR code for .apk)" - wait for build - QR code display.
6.  On phone - Open MIT AI2 Companion app - Touch "scan QR code" - point phone to QR on browser.
7.  "Allow Install" as screens appear on phone - open app.


## Directories
---
Directory Name | Files & Description
---|---
App_inventor | OSCAIL_app.aia - file to import to Mit App Inventor | Oscail.png - app icon
arduino | arduino_code.ino - code for UNO | wifi_code.ino - code for ESP8266
images | All images for README.md
## Author
---
Damon Nyhan| EM - damon.nyhan@gmail.com| Follow - D9@anovacap
Erwin Gove | EM - erwinhgove@gmail.com | Follow - @ErwinEhg50
