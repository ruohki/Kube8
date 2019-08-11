#include <Arduino.h>

#include <FS.h>

#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <ArduinoJson.h>

class Webserver {
  private:
    AsyncWebServer * _webserver;
    AsyncWebSocket * _websocket;

  // callbacks
  void onNotFound(AsyncWebServerRequest* request);
  void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);

  public:
    Webserver(uint16_t port = 80);
    ~Webserver();


    AsyncWebServer * getRawWebserver() {
      return _webserver;
    };
};