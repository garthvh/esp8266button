# esp8266 IoT Button using Github Actions

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/sparkfun_thing.jpg "Thing Enclosure")
[Customized Project Enclosure - Thingiverse](http://www.thingiverse.com/thing:981124)

An IoT Button using an ESP8266 WiFI microcontroller, a push button and github actions.  Posts to a github actions endpoint which updates a comment on an issue specific to each button.

I originally built this project using the IFTTT maker channel sending text messages, and then switched to updating a github issue once text messages were no longer free.  Since IFTTT itself is no longer free I wrote a third sketch using GitHub Actions. I want to replace my bespoke captive portal but have not found a plugin I like yet.

I soldered male pins on my Huzzah, and added female headers to my Sparkfun Thing. The thing did not come with any headers and male headers were included with the Huzzah.

I was able to program both with my [FTDI Friend](https://www.adafruit.com/product/284), you will need to cut the default RTS jumper on the back of the FTDI Friend (used by the Huzzah) and connect the DTR jumper to program the thing. Once cut it has been pretty easy to switch back and forth by soldering the jumpers as needed.

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/button_assembly.jpg "Huzzah Assembly")

The built in battery and charging circuit on the ESP8266 Thing really makes it easy to work with. By cutting the DTR trace on the bottom of the board and installing pins for a jumper I am able to program the thing with the jumper installed, and debug over serial with it removed.

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/sparkfun_thing_circuit.jpg "Thing Assembly")

Since flashing the device each time to configure WiFi was a pain I added some code that creates an Access Point and allows the user to configure the wireless network via their mobile device. I created a slimmed down version of [base css](http://getbase.org/) to style the pages served by the ESP8266.

I used an interesting hack I ran across, it serves the WiFi configuration page for any requests that result in a 404(Not Found) HTTP code creating a captive portal (like you seen in hotels or guest networks). By returning the configuration page for 404 requests it allows easy configuration no matter what page your mobile device OS requires. Once the device is connected a status page is available to check on your button and reset WiFi settings if necessary. This works perfectly on iOS devices and has been hit or miss on Android.  On Android if the captive portal does not work automatically you can always hit the root IP of the access point to view the configuration page.

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


## Enclosure
Using this awesome [Parametric and Customizable Project Enclosure](http://www.thingiverse.com/thing:155001) I made customized enclosures that fit the parts I was using for my buttons.

![Customized  Project Enclosure](http://garthvh.com/assets/img/esp8266/button_enclosure_green.jpg "Customized Project Enclosure")

[Customized Project Enclosure - Thingiverse](http://www.thingiverse.com/thing:941755)
