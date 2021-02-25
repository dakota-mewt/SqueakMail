
#include <WiFi.h>
#include <HTTPClient.h>
//EDIT THESE VARIABLES/////
const char* ssid = "TBD";  //Replace TBD with your Wifi SSID
const char* password = "TBD"; //Replace TBD with your Wifi password
const char* serverName = "TBD"; //Replace TBD with your IFTTT API Key
unsigned long timerDelay = 30000;  //how often you get emails once a mouse has been trapped.  30000 = 30 seconds
///////////////////////////
unsigned long lastTime = 0;
unsigned long trapTime = 0;
bool mouseTrapped = false;

#define ONBOARD_LED  2

#define IR 12
int detection = HIGH;
void setup() {
  Serial.begin (9600);
  pinMode(IR, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(ONBOARD_LED,OUTPUT);  
//  pinMode(led, OUTPUT);
//  pinMode(led2, OUTPUT);
    digitalWrite(ONBOARD_LED,HIGH);
    delay(100);
    digitalWrite(ONBOARD_LED,LOW);
    delay(100);
    digitalWrite(ONBOARD_LED,HIGH);
    delay(100);
    digitalWrite(ONBOARD_LED,LOW);
    delay(100);
    digitalWrite(ONBOARD_LED,HIGH);
    delay(100);
    digitalWrite(ONBOARD_LED,LOW);    
String httpRequestData = "value1=" + String("trap #1 initiated");
Serial.println(httpRequestData);
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
     http.begin(serverName);
     http.addHeader("Content-Type", "application/x-www-form-urlencoded");
     int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
    }
}
void loop() {
  detection = digitalRead(IR);

  if (mouseTrapped != true) {
    trapTime = millis();
  }
  unsigned long trapDays = millis() / 1000 / 60 / 60 / 24;
  unsigned long trapHours = ((millis() - (trapDays * 1000 * 60 * 60 * 24)) / 1000 / 60 / 60);
  unsigned long trapMinutes = (millis() - (trapDays * 1000 * 60 * 60 * 24) - (trapHours * 1000 * 60 * 60)) / 1000 / 60;
  unsigned long trapSeconds = (millis() - (trapDays * 1000 * 60 * 60 * 24) - (trapHours * 1000 * 60 * 60) - (trapMinutes * 1000 * 60)) / 1000;

  unsigned long mouseDays = millis() / 1000 / 60 / 60 / 24;
  unsigned long mouseHours = ((millis() - trapTime - (mouseDays * 1000 * 60 * 60 * 24)) / 1000 / 60 / 60);
  unsigned long mouseMinutes = (millis() - trapTime - (mouseDays * 1000 * 60 * 60 * 24) - (mouseHours * 1000 * 60 * 60)) / 1000 / 60;
  unsigned long mouseSeconds = (millis() - trapTime - (mouseDays * 1000 * 60 * 60 * 24) - (mouseHours * 1000 * 60 * 60) - (mouseMinutes * 1000 * 60)) / 1000;
  
  String httpRequestData = "value1=" + String("trap #1 has been running for ") + trapDays + String(" days ") + 
  trapHours + String(" hours ") + trapMinutes + String(" minutes ") + trapSeconds + String(" seconds. ") + 
  "&value2=" + String("Mouse has been trapped for ") + mouseDays + String(" days ") + 
  mouseHours + String(" hours ") + mouseMinutes + String(" minutes ") +
  mouseSeconds + String(" seconds");            
  Serial.println(httpRequestData);

  if(detection == LOW){ 
    digitalWrite(ONBOARD_LED,HIGH); // When the Red condition is met, the Green LED should turn off
    mouseTrapped = true;
    if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
      if(WiFi.status()== WL_CONNECTED){
        HTTPClient http;
        
        // Your Domain name with URL path or IP address with path
        http.begin(serverName);
        
        // Specify content-type header
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        // Data to send with HTTP POST
        //String httpRequestData = "value1=" + String("trap #1 has been running for ") + String(millis() / 1000) + String(" seconds. ") + String("Mouse has been trapped for ") + String((millis() - trapTime)/1000) + String(" seconds");            
        // Send HTTP POST request
        int httpResponseCode = http.POST(httpRequestData);
        
        
        /*
        // If you need an HTTP request with a content type: application/json, use the following:
        http.addHeader("Content-Type", "application/json");
        // JSON data to send with HTTP POST
        String httpRequestData = "{\"value1\":\"" + String(random(40)) + "\",\"value2\":\"" + String(random(40)) + "\",\"value3\":\"" + String(random(40)) + "\"}";
        // Send HTTP POST request
        int httpResponseCode = http.POST(httpRequestData);
        */
     
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
  
          
        // Free resources
        //http.end();
  
      }
      else {
      Serial.println("WiFi Disconnected");
      }
    lastTime = millis();
    }
  }
  else {
    digitalWrite(ONBOARD_LED,LOW);
  }
  delay(1000);
}
