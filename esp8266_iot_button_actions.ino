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

// Variables
const char* ssid = "your_ssid"; // Name of the Host
const char* password = "your_psk"; // Password of the corresponding Host
const char* github_user = "your_github_user"; // GitHub User for running action
const char* github_repo = "your_github_repo";
const char* github_token = "your_github_token";
const char* host = "api.github.com"; // Server from which data is to be fetched
const int httpsPort = 443; // Default port for HTTPS 

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "35 85 74 ef 67 35 a7 ce 40 69 50 f3 c0 f6 80 cf 80 3b 2e 19"; // Fingerprint/Thumbprint for website api.github.com
                         
void setup() {

  // Start Serial
  Serial.begin(115200);
  Serial.println();
  
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
  // /repos/{owner}/{repo}/actions/workflows/{workflow_id}/dispatches
  String url = "https://api.github.com/repos/" + String(github_user) + "/" + String(github_repo) + "/actions/workflows/manual.yml/dispatches"; //address from which we need to get the data inside the server.
  String data = "{\"ref\":\"main\"}"; // post the tag or branch you want the action to run against
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
    Serial.printf("[HTTPS] Unable to connect\n");
  }
  Serial.println("closing connection");
}

void loop() {
  
}