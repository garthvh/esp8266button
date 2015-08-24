# esp8266 Dash Like IoT Button using IFTTT

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/sparkfun_thing.jpg "Thing Enclosure")
[Customized Project Enclosure - Thingiverse](http://www.thingiverse.com/thing:981124)

An IoT Button using an Adafruit Huzzah or Sparkfun Thing, a push button and the IFTTT Maker Channel (or any other http endpoint).  Posts JSON data to IFTTT Maker Channel event when the button is pressed.

I soldered male pins on my Huzzah, and added female headers to my Sparkfun Thing. The thing did not come with any headers and male headers were included with the Huzzah.

I was able to program both with my [FTDI Friend](https://www.adafruit.com/product/284), you will need to cut the default RTS jumper on the back of the FTDI Friend (used by the Huzzah) and connect the DTR jumper to program the thing. Once cut it has been pretty easy to switch back and forth by soldering the jumpers as needed.

I still need to write some sleep code to be more efficient on battery use.

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/button_assembly.jpg "Huzzah Assembly")

The built in battery and charging circuit on the ESP8266 Thing really makes it easy to work with. I have not been able to get serial debugging output working with the thing.

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/sparkfun_thing_circuit.jpg "Thing Assembly")

## Setup
Requires an arduino ide version > 1.6.4

Set up your [Arduino IDE board manager](https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide)  to support the Huzzah breakout board.

## BOM

### Adafruit Huzzah

* [Adafruit Huzzah](https://www.adafruit.com/products/2471)
* [Arcade Button](https://www.sparkfun.com/products/9339)
* Standard RGB LCD
* 4 M3 20MM Hex Screws
* AAA Battery Pack
* Female Jumper wires

### Sparkfun Thing

* [Sparkfun Thing](https://www.sparkfun.com/products/13231)
* [Panel Mount Push Button](https://www.adafruit.com/products/1504)
* Standard Green LCD
* 4 M3 20MM Hex Screws
* [150 mAh LiPo Battery](https://www.adafruit.com/product/1317)
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
Using this awesome [Parametric and Customizable Project Enclosure](http://www.thingiverse.com/thing:155001) I made customized enclosures that fit the parts I was using for my buttons.

![Customized  Project Enclosure](http://garthvh.com/assets/img/esp8266/button_enclosure_green.jpg "Customized Project Enclosure")

[Customized Project Enclosure - Thingiverse](http://www.thingiverse.com/thing:941755)
