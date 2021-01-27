# esp8266 IoT Button using Github Actions

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/sparkfun_thing.jpg "Thing Enclosure")
[Customized Project Enclosure - Thingiverse](http://www.thingiverse.com/thing:981124)

## Software

An IoT Button using an ESP8266 WiFI microcontroller, a push button and github actions. POSTS to a [GitHub Actions Workflow dispatch event]( https://docs.github.com/en/rest/reference/actions#create-a-workflow-dispatch-event) endpoint which updates a comment on an issue specific to each button.

I originally built this project using the IFTTT maker channel sending text messages, then switched to updating a github issue once text messages were no longer free.  Now that IFTTT itself is no longer free I wrote a third sketch using GitHub Actions. This makes for a simpler demo anyways as the only service involved is GitHub and everything is stored in code. You can see the ReadMe with instructions from the original IFTTT project [here](https://github.com/garthvh/esp8266button/wiki/Original-IFTTT-Readme)

The github actions workflow YML file update-issue-comment.yml is also in this repository and you can see the button press comments on the issue i have created for my SparkFun Thing button.

You will need the following settings in the arduino sketch <code>esp8266_iot_button_actions.ino</code>:

        // WiFi and GitHub Variables
        const char* ssid = "YOUR_SSID"; // SSID For the WiFi network you want to connect to
        const char* password = "YOUR_PSK"; // PSK For the WiFi network you want to connect to
        const char* github_user = "YOUR_GITHUB_USERNAME"; // GitHub User for running action
        const char* github_repo = "YOUR_GITHUB_REPO"; // GitHub Repo where action lives
        const char* github_token = "YOUR_GITHUB_TOKEN"; // GitHub Authorization Token
        const char* github_workflow_id = "YOUR_WORKFLOW_YML_FILE"; // Workflow YML file name
        const char* host = "api.github.com"; // Server from which data is to be fetched
        const int httpsPort = 443; // Default port for HTTPS 


You will also need to copy the YML from the action in this repository and create a new issue where the comments from the button will go.  The issue number in the YML file should be updated to the number of the newly created issue.

## Hardware

I soldered male pins on my Huzzah, and added female headers to my Sparkfun Thing. The thing did not come with any headers and male headers were included with the Huzzah.

I was able to program both with my [FTDI Friend](https://www.adafruit.com/product/284), you will need to cut the default RTS jumper on the back of the FTDI Friend (used by the Huzzah) and connect the DTR jumper to program the thing. Once cut it has been pretty easy to switch back and forth by soldering the jumpers as needed.

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/button_assembly.jpg "Huzzah Assembly")

The built in battery and charging circuit on the ESP8266 Thing really makes it easy to work with. By cutting the DTR trace on the bottom of the board and installing pins for a jumper I am able to program the thing with the jumper installed, and debug over serial with it removed.

![Enclosure Assembly](http://garthvh.com/assets/img/esp8266/sparkfun_thing_circuit.jpg "Thing Assembly")

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
