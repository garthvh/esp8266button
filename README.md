# esp8266 Dash Like IoT Button using IFTTT

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/sparkfun_thing.jpg "Thing Enclosure")
[Customized Project Enclosure - Thingiverse](http://www.thingiverse.com/thing:981124)

An IoT Button using an Adafruit Huzzah or Sparkfun Thing, a push button and the IFTTT Maker Channel (or any other http endpoint).  Posts JSON data to IFTTT Maker Channel event when the button is pressed.

I soldered male pins on my Huzzah, and added female headers to my Sparkfun Thing. The thing did not come with any headers and male headers were included with the Huzzah.

I was able to program both with my [FTDI Friend](https://www.adafruit.com/product/284), you will need to cut the default RTS jumper on the back of the FTDI Friend (used by the Huzzah) and connect the DTR jumper to program the thing. Once cut it has been pretty easy to switch back and forth by soldering the jumpers as needed.

I still need to write some sleep code to be more efficient on battery use.

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/button_assembly.jpg "Huzzah Assembly")

The built in battery and charging circuit on the ESP8266 Thing really makes it easy to work with. By cutting the DTR trace on the bottom of the board and installing pins for a jumper I am able to program the thing with the jumper installed, and debug over serial with it removed.

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/sparkfun_thing_circuit.jpg "Thing Assembly")

Since flashing the device each time to configure WiFi was a pain I added some code that creates an Access Point and allows the user to configure the wireless network via their mobile device. I created a slimmed down version of [base css](http://getbase.org/) to style the pages served by the ESP8266. I used an interesting hack I ran across, it serves the WiFi configuration page for any requests that result in a 404(Not Found) HTTP code. Mobile devices apparently try and hit some specific page for login when they connect and don't have internet (like you seen in hotels or guest networks) and by returning the configuration page for 404 requests it allows easy configuration no matter what page your mobile device OS requires. Once the device is connected a status page is available to check on your button and reset WiFi settings if necessary.

![WiFi Setup](http://garthvh.com/assets/img/esp8266/wifi_setup_all.png "WiFi Setup")

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

## Device Configuration

At the top of the esp8266_iot_button.ino file are the configuration options for the device. You will need to replace the placeholder values with your KEY and EVENT for IFTTT. You can create your own SSID name for configuration mode and you can optionally turn on a RGB LED.

    const char* AP_SSID = "ESP8266_IOT_BUTTON_SETUP";
    ////////////////////////
    // Device Definitions //
    ////////////////////////
    String DEVICE_TITLE = "IFTTT ESP8266 Dash Like Button";
    const char* AP_SSID = "ESP8266_IOT_BUTTON_SETUP";
    boolean POWER_SAVE = false;

    ///////////////////////
    // IFTTT Definitions //
    ///////////////////////
    const char* IFTTT_URL= "maker.ifttt.com";
    const char* IFTTT_KEY= "YOUR IFTTT_KEY";
    const char* IFTTT_EVENT = "YOUR_IFTTT_EVENT";
    const char* IFTTT_NOTIFICATION_EVENT = "YOUR_IFTTT_NOTIFICATION_EVENT";

## IFTTT Events

You will need to setup the IFTTT Maker Channel and two IFTTT recipes, one for the button event, and one for the notification that the webserver is up with WiFi SSID and IP address.

![IFTTT Recipes](http://garthvh.com/assets/img/esp8266/ifttt_recipes_screenshot.png "IFTTT Recipes")

## Enclosure
Using this awesome [Parametric and Customizable Project Enclosure](http://www.thingiverse.com/thing:155001) I made customized enclosures that fit the parts I was using for my buttons.

![Customized  Project Enclosure](http://garthvh.com/assets/img/esp8266/button_enclosure_green.jpg "Customized Project Enclosure")

[Customized Project Enclosure - Thingiverse](http://www.thingiverse.com/thing:941755)

## Requirements

* [Arduino core for ESP8266 WiFi chip](https://github.com/esp8266/Arduino)
