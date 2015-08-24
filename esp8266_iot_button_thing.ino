
/*----------------------------------------------------------------------------
  Simple IoT button using the If This Then That(IFTTT) Maker Channel, Sparkfun
  ESP8266 Thing, a standard Green LCD and a push button.

  While attempting to connect to the specified SSID the LCD flashes,
  when connected the led remains green, while data is sending the led turns
  off, when done it turns back to green.
  ----------------------------------------------------------------------------*/

#include <ESP8266WiFi.h>

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

/////////////////////
// Pin Definitions //
/////////////////////
const int LED_GREEN = 5;
const int BUTTON_PIN = 0;

//////////////////////
// Button Variables //
//////////////////////
int BUTTON_STATE;
int LAST_BUTTON_STATE = LOW;
long LAST_DEBOUNCE_TIME = 0;
long DEBOUNCE_DELAY = 50;
int BUTTON_COUNTER = 0;

void setup() {
  // Setup Pins
  initHardware();

  // Connect to WiFi
  connectWiFi();

  // Turn the status led Green when the WiFi has been connected
  digitalWrite(LED_GREEN, HIGH);
}

void loop() {
  // Wait for button Presses
  boolean pressed = debounce();
  if (pressed == true) {
    BUTTON_COUNTER++;
    if(BUTTON_COUNTER > 1)
    {
      triggerIFTTTEvent();
    }
  }
}

void initHardware()
{
  // LEDS
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_GREEN, LOW);

  // Button
  pinMode(BUTTON_PIN, INPUT);
}

void triggerIFTTTEvent()
{
  // Turn off the Green LED  while transmitting.
  digitalWrite(LED_GREEN, LOW);

  // Define the WiFi Client
  WiFiClient client;
  // Set the http Port
  const int httpPort = 80;

  // Make sure we can connect
  if (!client.connect(IFTTT_URL, httpPort)) {
    return;
  }

  // We now create a URI for the request
  String url = "/trigger/" + String(IFTTT_EVENT) + "/with/key/" + String(IFTTT_KEY);

  // Set some values for the JSON data
  String value_1 = String(BUTTON_COUNTER -1);
  String value_2 = String(WiFi.localIP());
  String value_3 = String(WiFi.gatewayIP());

  // Build JSON data string
  String data = "";
  data = data + "\n" + "{\"value1\":\""+ value_1 +"\",\"value2\":\""+ value_2 +"\",\"value3\":\""+ value_3 + "\"}";

  // Post the button press to IFTTT
  if (client.connect(IFTTT_URL, httpPort)) {

     // Sent HTTP POST Request with JSON data
     client.println("POST "+ url +" HTTP/1.1");
     client.println("Host: "+ String(IFTTT_URL));
     client.println("User-Agent: Arduino/1.0");
     client.print("Accept: *");
     client.print("/");
     client.println("*");
     client.print("Content-Length: ");
     client.println(data.length());
     client.println("Content-Type: application/json");
     client.println("Connection: close");
     client.println();
     client.println(data);
  }
   // After a successful send turn the light back to green
   digitalWrite(LED_GREEN, HIGH);
}

// Debounce Button Presses
boolean debounce() {
  boolean retVal = false;
  int reading = digitalRead(BUTTON_PIN);
  if (reading != LAST_BUTTON_STATE) {
    LAST_DEBOUNCE_TIME = millis();
  }
  if ((millis() - LAST_DEBOUNCE_TIME) > DEBOUNCE_DELAY) {
    if (reading != BUTTON_STATE) {
      BUTTON_STATE = reading;
      if (BUTTON_STATE == HIGH) {
        retVal = true;
      }
    }
  }
  LAST_BUTTON_STATE = reading;
  return retVal;
}

// Connect to WiFi from SparkFun
void connectWiFi()
{
  byte ledStatus = LOW;

  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);
  // WiFI.begin([ssid], [passkey]) initiates a WiFI connection
  // to the stated [ssid], using the [passkey] as a WPA, WPA2,
  // or WEP passphrase.
  WiFi.begin(WIFI_SSID, WIFI_PSK);

  // Use the WiFi.status() function to check if the ESP8266
  // is connected to a WiFi network.
  while (WiFi.status() != WL_CONNECTED)
  {
    // Blink the LED
    digitalWrite(LED_GREEN, ledStatus); // Write LED high/low
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;

    // Delays allow the ESP8266 to perform critical tasks
    // defined outside of the sketch. These tasks include
    // setting up, and maintaining, a WiFi connection.
    delay(100);
    // Potentially infinite loops are generally dangerous.
    // Add delays -- allowing the processor to perform other
    // tasks -- wherever possible.
  }
}
