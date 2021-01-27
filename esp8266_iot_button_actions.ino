/*
 *  Use HTTPS to trigger a GitHub Action
 *
 *  Created by Garth Vander Houwen, 2021.
 *  
 */
// Libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// WiFi and GitHub Variables
const char* ssid = "YOUR_SSID"; // SSID For the WiFi network you want to connect to
const char* password = "YOUR_PSK"; // PSK For the WiFi network you want to connect to
const char* github_user = "YOUR_GITHUB_USERNAME"; // GitHub User for running action
const char* github_repo = "YOUR_GITHUB_REPO"; // GitHub Repo where action lives
const char* github_token = "YOUR_GITHUB_TOKEN"; // GitHub Authorization Token
const char* github_workflow_id = "YOUR_WORKFLOW_YML_FILE"; // Workflow YML file name
const char* host = "api.github.com"; // Server from which data is to be fetched
const int httpsPort = 443; // Default port for HTTPS 

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "35 85 74 ef 67 35 a7 ce 40 69 50 f3 c0 f6 80 cf 80 3b 2e 19"; // Fingerprint/Thumbprint for website api.github.com

// Button Variables
const int buttonPin = 0;     // pushbutton pin
const int ledPin = 4;       // LED pin

int ledState = LOW;         // current state of LED
int buttonState = LOW;             // current state of button
int lastButtonState = LOW;   // previous state of button

unsigned long lastDebounceTime = 0; // last toggle
unsigned long debounceDelay = 50;   // debounce time

void setup() {

  // Start Serial
  Serial.begin(115200);
  Serial.println();
  Serial.println("....");
  Serial.println("....");
  delay (5000);
  // Connect WiFi
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Print out the Local IP assigned by the router to ESP8266
}

void loop() {
  int reading = digitalRead(buttonPin); //read

  if (reading != lastButtonState) // If the switch changed
  {
    lastDebounceTime = millis();  // reset the debouncing
  }
  //check if debounce time > 50ms
  if ((millis() - lastDebounceTime) > debounceDelay)
  { if (reading != buttonState)
    { buttonState = reading;
      if (buttonState == LOW)
      {
        Serial.println("button pressed");
        SendDispatch();
      }
    }
  }
  lastButtonState = reading;       // save the reading
}

void SendDispatch(){
  
  // Setup HTTPS Client
  WiFiClientSecure client;  // Use WiFiClientSecure class to create client instance
  Serial.print("connecting to ");
  Serial.println(host);
  client.setInsecure();

  // Connect with the server api.github.com at port 443
  if (!client.connect(host, httpsPort)) { 
      Serial.println("connection failed");
      return;
  }
  
  // Verify fingerprint 
  if (client.verify(fingerprint, host)) { 
      Serial.println("certificate matches");
  } 
  else {
      Serial.println("certificate doesn't match");
  }

  // Execute a POST request to create a workflow dispatch event
  // https://docs.github.com/en/rest/reference/actions#create-a-workflow-dispatch-event
  
  // Parameters
  // Name         Type    In      Description
  // ------------|-------|-------|----------
  // accept       string  header  Setting to application/vnd.github.v3+json is recommended.
  // owner        string  path  
  // repo         string  path  
  // workflow_id  string  path    The ID of the workflow. You can also pass the workflow file name as a string.
  // ref          string  body    Required. The git reference for the workflow. The reference can be a branch or tag name.
  // inputs       object  body    Input keys and values configured in the workflow file. The maximum number of properties is 10. Any default properties configured in the workflow file will be used when inputs are omitted.

  // GitHub Actions API URL /repos/{github_user}/{github_repo}/actions/workflows/{github_workflow_id}/dispatches
  String url = "https://api.github.com/repos/" + String(github_user) + "/" + String(github_repo) + "/actions/workflows/" + String(github_workflow_id) + "/dispatches"; 

  // JSON data with the tag or branch you want the action to run against pass up to 10 custom inputs
  String data = "{\"ref\":\"main\",\"inputs\":{\"button_name\":\"SparkFun Thing #76\"}}"; 

  HTTPClient https;
  Serial.println("Starting https client");
  if (https.begin(client, url)) {
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", "token " + String(github_token));
    Serial.println("posting to the github api");
    int httpCode = https.POST(data);
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("POST http status code: %d\n", httpCode);
      // handle response
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_NO_CONTENT || HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println("successfully posted the following JSON data");
        Serial.println(data);
      }
    } 
    else {
      Serial.printf("POST failed, error: %s\n", https.errorToString(httpCode).c_str());
      String payload = https.getString();
      Serial.println("failed to post the following JSON data");
      Serial.println(payload);
    }
    https.end();
  } 
  else {
    Serial.printf("unable to connect\n");
  }
  Serial.println("closing connection");
  
}
