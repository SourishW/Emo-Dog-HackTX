#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "images.h"
#include "Movement.h"

TFT_eSPI tft;
char* ssid = "emodog";
char* pass = "abcd1234$";
String serverName = "http://192.168.137.207:8080/";
String serverPath;
String payload;
Vehicle doggo;
void setup() {
  Serial.begin(115200);
  Serial.println("Serial Initialized");
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_CYAN);
  Serial.println("Should be Cyan");
  Serial.printf("Connecting to WiFi network %s\n", ssid);
  doggo.init();
  WiFi.begin(ssid, pass);
  while(WiFi.status()!=WL_CONNECTED);
  Serial.println("Connection Successful");
  // tft.draw16BitBitmap(0,0,happy_pug, 306,204);
  tft.fillRect(20+20,40,80,80,ILI9341_DARKGREY);
  tft.fillRect(200,40,80,80,ILI9341_DARKGREY);
  tft.fillRect(80-5,140+20,120+20+20+10,60, ILI9341_RED);
  Serial.println("Printed test BMP");
  // tft.fillRect(0,0, 50,100,ILI9341_DARKGREEN);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()==WL_CONNECTED){
    HTTPClient http;
    serverPath = serverName; // add the path if needed
    http.begin(serverPath);
    int http_response = http.GET();
    Serial.printf("HTTP RESPONSE: %d\n", http_response);
    if(http_response > 0){
      Serial.println("HTTP RESPONSE: ");
      Serial.println(http_response);
      String payload = http.getString();
      Serial.println(payload);
    }else{

    }

    http.end();
    delay(5000);

  }else{
    Serial.printf("Status :%d\n", WiFi.status());
  }
  


}
