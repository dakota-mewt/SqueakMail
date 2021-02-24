
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Ginger5";
const char* password = "yankees1";
const char* serverName = "https://maker.ifttt.com/trigger/Mouse_Trapped/with/key/bAnUYxd-W1NSR8wYVt0uI4";
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
unsigned long trapTime = 0;
bool mouseTrapped = false;

#define ONBOARD_LED  2

#define trigPin 13
#define echoPin 12

//#define led 11
//#define led2 10

void setup() {
  Serial.begin (9600);


  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


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
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
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

  if (distance < 10) {  // This is where the LED On/Off happens
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
      http.end();
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
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");    
  }
  delay(1000);
}
