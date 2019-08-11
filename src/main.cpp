#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWiFiManager.h>
#include <FS.h>
#include <FastLED.h>

#include "webserver.h"

#define LED_PIN  D4

#define COLOR_ORDER GRB
#define CHIPSET     WS2811

#define BRIGHTNESS 64

DNSServer dns;

Webserver * webserver;

void configModeCallback (AsyncWiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void loop()
{

}

void setup() {
  Serial.begin(9600);

  AsyncWebServer * captiveWebserver = new AsyncWebServer(80);
  AsyncWiFiManager * wifiManager = new AsyncWiFiManager(captiveWebserver ,&dns);
  

  wifiManager->setAPCallback(configModeCallback);

  if(!wifiManager->autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    ESP.reset();
    delay(1000);
  }

  Serial.println("connected...yeey :)");
  captiveWebserver->reset();
  delete captiveWebserver;
  
  SPIFFS.begin();

  webserver = new Webserver(80);
  webserver->getRawWebserver()->on("/resetwifi", HTTP_GET, [wifiManager](AsyncWebServerRequest *request){
    wifiManager->resetSettings();
    ESP.reset();
  });
  
}