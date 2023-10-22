#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "images.h"
#include "Movement.h"
#include <esp_timer.h>

void actions(int);
void displayTests(void);
TFT_eSPI tft;
char* ssid = "HowWasYourDayToday";
char* pass = "9563987865";
String serverName = "http://192.168.50.158:8080/";
String serverPath;
String payload;
Vehicle doggo;
#define BEHAVIORS_PER_EMOTION 5
#define NEW_DATA_PERIOD_S 5 // in seconds 

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Initialized");
  Serial.println("Initializing Display ...");
  tft.begin();
  tft.fillScreen(ILI9341_WHITE);
  tft.setRotation(3);
  Serial.println("Display Initialized");
  Serial.printf("Connecting to WiFi network %s\n", ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status()!=WL_CONNECTED);
  Serial.println("Connection Successful");
  Serial.println("Initializing Motors");
  doggo.init();
  doggo.setSpeed(0);
  Serial.println("Initalized Motors");
}

void loop() {
  // put your main code here, to run repeatedly:
  // displayTests();
  if(WiFi.status()==WL_CONNECTED){
    Serial.println("Connecting to HTTP Server");
    HTTPClient http;
    serverPath = serverName; // add the path if needed
    http.begin(serverPath);
    int http_response = http.GET();
    if(http_response > 0){
      Serial.println("HTTP Get successful");
      String payload = http.getString();
      Serial.println(payload);
      actions(payload.c_str()[0]-'0');
    }else{
      Serial.printf("HTTP Response: %d\n", http_response);
    }
    http.end();
  }

}
// ["angry", "disgust", "fear", "happy", "sad", "surprise", "neutral"
#define ANGRY_INDEX 0
#define DISGUST_INDEX 1
#define FEAR_INDEX 2
#define HAPPY_INDEX 3
#define SAD_INDEX 4
#define SURPRISE_INDEX 5
#define NEUTRAL_INDEX 6
void actions(int val){
    switch (val)
    {
    case ANGRY_INDEX:
      for ( int i = 0 ; i < BEHAVIORS_PER_EMOTION ; i++){
        switch (i)
      {
      case 0:
        tft.draw16BitBitmap(40,40,surprisedEye,80,80);
        tft.draw16BitBitmap(40+200,40,surprisedEye,80,80);
        tft.draw16BitBitmap(75,160,disgustMouth,170,60);
        doggo.setSpeed(-64);
        break;
      case 1:
        tft.draw16BitBitmap(40,40,surprisedEye,80,80);
        tft.draw16BitBitmap(40+200,40,surprisedEye,80,80);
        tft.draw16BitBitmap(75,160,surprisedMouth,170,60);
        doggo.setSpeed(0);
        break;
      
      default:
      doggo.setSpeed(0);
        break;
      }
      delayMicroseconds(NEW_DATA_PERIOD_S*1000000/BEHAVIORS_PER_EMOTION);
    }
      break;
    
    case DISGUST_INDEX:
    for ( int i = 0 ; i < BEHAVIORS_PER_EMOTION ; i++){
      delayMicroseconds(NEW_DATA_PERIOD_S*1000000/BEHAVIORS_PER_EMOTION);
      switch (i)
      {
      case 0:
        tft.draw16BitBitmap(40,40,blankEye,80,80);
        tft.draw16BitBitmap(40+200,40,blankEye,80,80);
        tft.draw16BitBitmap(75,160,disgustMouth,170,60);
        doggo.setSpeed(-64);
        break;
      case 1:
        tft.draw16BitBitmap(40,40,blankEye,80,80);
        tft.draw16BitBitmap(40+200,40,blankEye,80,80);
        tft.draw16BitBitmap(75,160,neutralMouth,170,60);
        doggo.setSpeed(0);
        break;
      
      default:
      doggo.setSpeed(0);
        break;
      }
    }
      break;

    case FEAR_INDEX:
      for ( int i = 0 ; i < BEHAVIORS_PER_EMOTION ; i++){
        switch (i%2)
      {
      case 0:
        tft.draw16BitBitmap(40,40,surprisedEye,80,80);
        tft.draw16BitBitmap(40+200,40,surprisedEye,80,80);
        tft.draw16BitBitmap(75,160,surprisedMouth,170,60);
        doggo.setSpeed(-64);
        break;
      case 1:
        tft.draw16BitBitmap(40,40,surprisedEye,80,80);
        tft.draw16BitBitmap(40+200,40,surprisedEye,80,80);
        tft.draw16BitBitmap(75,160,disgustMouth,170,60);
        doggo.setSpeed(64);
        break;
      
      default:
      doggo.setSpeed(0);
        break;
      }
      delayMicroseconds(NEW_DATA_PERIOD_S*1000000/BEHAVIORS_PER_EMOTION);
    }
      break;

    case HAPPY_INDEX:
    for ( int i = 0 ; i < BEHAVIORS_PER_EMOTION ; i++){
      switch (i)
      {
      case 0:
        tft.draw16BitBitmap(40,40,happyEyeLeft,80,80);
        tft.draw16BitBitmap(40+200,40,happyEyeRight,80,80);
        tft.draw16BitBitmap(75,160,surprisedMouth,170,60);
        doggo.setSpeed(64);
        break;
      case 1:
        tft.draw16BitBitmap(40,40,surprisedEye,80,80);
        tft.draw16BitBitmap(40+200,40,surprisedEye,80,80);
        tft.draw16BitBitmap(75,160,surprisedMouth,170,60);
        doggo.setSpeed(-64);
        break;
      default:
      doggo.setSpeed(0);
        break;
      }
      delayMicroseconds(NEW_DATA_PERIOD_S*1000000/BEHAVIORS_PER_EMOTION);
    }
      break;

    case SAD_INDEX:
      doggo.setSpeed(0);
      for ( int i = 0 ; i < BEHAVIORS_PER_EMOTION ; i++){
        switch (i)
      {
      case 0:
        tft.draw16BitBitmap(40,40,happyEyeLeft,80,80);
        tft.draw16BitBitmap(40+200,40,blankEye,80,80);
        tft.draw16BitBitmap(75,160,disgustMouth,170,60);
        doggo.setSpeed(64);
        break;
      case 1:
        tft.draw16BitBitmap(40,40,blankEye,80,80);
        tft.draw16BitBitmap(40+200,40,happyEyeRight,80,80);
        tft.draw16BitBitmap(75,160,surprisedMouth,170,60);
        doggo.setSpeed(-64);
        break;
      default:
      doggo.setSpeed(0);
        break;
      }
      delayMicroseconds(NEW_DATA_PERIOD_S*1000000/BEHAVIORS_PER_EMOTION);
    }
      break;
    case SURPRISE_INDEX:
    for ( int i = 0 ; i < BEHAVIORS_PER_EMOTION ; i++){
      switch (i%2)
      {
      case 0:
        tft.draw16BitBitmap(40,40,surprisedEye,80,80);
        tft.draw16BitBitmap(40+200,40,happyEyeRight,80,80);
        tft.draw16BitBitmap(75,160,surprisedMouth,170,60);

        doggo.setSpeed(64);
        break;
      case 1:
        tft.draw16BitBitmap(40,40,happyEyeRight,80,80);
        tft.draw16BitBitmap(40+200,40,surprisedEye,80,80);
        tft.draw16BitBitmap(75,160,surprisedMouth,170,60);
        doggo.setSpeed(-64);
        break;
      default:
      doggo.setSpeed(0);
        break;
      }
      delayMicroseconds(NEW_DATA_PERIOD_S*1000000/BEHAVIORS_PER_EMOTION);
    }
      break;
    case NEUTRAL_INDEX:
    for ( int i = 0 ; i < BEHAVIORS_PER_EMOTION ; i++){
        tft.draw16BitBitmap(40,40,blankEye,80,80);
        tft.draw16BitBitmap(40+200,40,blankEye,80,80);
        tft.draw16BitBitmap(75,160,neutralMouth,170,60);
      
      delayMicroseconds(NEW_DATA_PERIOD_S*1000000/BEHAVIORS_PER_EMOTION);
    }
      break;

    default:
      Serial.printf("%d\n", val);
      for ( int i = 0 ; i < BEHAVIORS_PER_EMOTION ; i++){
        
      delayMicroseconds(NEW_DATA_PERIOD_S*1000000/BEHAVIORS_PER_EMOTION);
    }
      break;
    }
}

void displayTests(){
  while(1){
    tft.draw16BitBitmap(40,40,blankEye,80,80);
    tft.draw16BitBitmap(40+200,40,blankEye,80,80);
    tft.draw16BitBitmap(75,160,disgustMouth,170,60);
    delay(3000);
    tft.draw16BitBitmap(40,40,happyEyeLeft,80,80);
    tft.draw16BitBitmap(40+200,40,happyEyeRight,80,80);
    tft.draw16BitBitmap(75,160,neutralMouth,170,60);
    delay(3000);
    tft.draw16BitBitmap(40,40,surprisedEye,80,80);
    tft.draw16BitBitmap(40+200,40,surprisedEye,80,80);
    tft.draw16BitBitmap(75,160,surprisedMouth,170,60);
    delay(3000);
  }
}


