# esp8266 IoT Button using IFTTT
An IoT Button using an Adafruit Huzzah or Sparkfun Thing, a push button and the IFTTT Maker Channel.  Posts JSON data to IFTTT Maker Channel event when the button is pressed.

## Setup
Requires an arduino ide version > 1.6.4

Set up your [Arduino IDE board manager](https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide)  to support the Huzzah breakout board.

## BOM

### Adafruit Huzzah

* Adafruit Huzzah
* Arcade Button
* Standard RGB LCD
* 4 M3 20MM Hex Screws
* AAA Battery Pack
* Female Jumper wires

### Sparkfun Thing

* Sparkfun Thing
* Panel Mount Push Button
* Standard Green LCD
* 4 M3 20MM Hex Screws
* 150MA LiPo Battery
* Male Jumper wires

## Configuration

At the top of the esp8266_iot_button.ino file you will need to replace the placeholder values with information on your WiFi SSID and Password, and your KEY and EVENT for IFTTT.

    //////////////////////
    // WiFi Definitions //
    //////////////////////
    const char WIFI_SSID[] = "YOUR_SSID";
    const char WIFI_PSK[] = "YOUR_PASSWORD";

    ///////////////////////
    // IFTTT Definitions //
    ///////////////////////
    const char* IFTTT_URL= "maker.ifttt.com";
    const char* IFTTT_KEY= "YOUR IFTTT_KEY";
    const char* IFTTT_EVENT = "YOUR_IFTTT_EVENT";

## Enclosure
![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/button_assembly.jpg "Enclosure Assembly")

![Customized  Project Enclosure](http://garthvh.com/assets/img/esp8266/button_enclosure_green.jpg "Customized Project Enclosure")

[Customized Project Enclosure - Thingiverse](http://www.thingiverse.com/thing:941755)
