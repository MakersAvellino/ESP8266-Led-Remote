#include <ESPAsyncWebServer.h> // asyncwebserver library
#include <ESPAsyncTCP.h> // asynchTCP need for asynchwebserver
#include <ESP8266WiFi.h> //wifi library, included into the esp8266 core
#include "index.h" //HTML webpage contents

//SSID and Password of your WiFi router
const char* ssid = "LenovoK6";
const char* password = "demagogo91";

AsyncWebServer server(80); //Server on port 80
AsyncWebSocket ws("/ws"); //the websocket will listen on the same port of the webserver but redirected to ws

int led = D4; // the led variable in associated to the D4 pin wich also controls the ESP onboard led

//==============================================================
//                  WEB SOCKET EVENT AND NOT FOUND ROUTINE
//==============================================================


void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) { // When a WebSocket message is received this happen
  if (type == WS_EVT_CONNECT) {
    //client connected
    os_printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->printf("Hello Client %u :)", client->id());
    client->ping();
  } else if (type == WS_EVT_DISCONNECT) {
    //client disconnected
    os_printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
  } else if (type == WS_EVT_ERROR) {
    //error was received from the other end
    os_printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if (type == WS_EVT_PONG) {
    //pong message was received (in response to a ping request maybe)
    os_printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char*)data : "");
  } else if (type == WS_EVT_DATA) { //this is the type wich correspond to the data, don't delete the above code
    char input;
    input = data[0]; // data in an array with a specified length defined by the len variable 
    if (input == '0') {
      digitalWrite(led, HIGH);
    } else {
      digitalWrite(led, LOW);
    }
  }
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) { // this load the web page when you connect to the esp
      request->send_P(200, "text/html", MAIN_page); //Send web page
    });

    server.on("/toggleLed", HTTP_GET, [](AsyncWebServerRequest * request) { // led routing controller for the webserver
      String OTA = request->getParam("testo")->value();
      if (OTA.equals("false")) {
        digitalWrite(led, HIGH);
      } else {
        digitalWrite(led, LOW);
      }

    });

    ws.onEvent(onWsEvent); // the onWsEvent reference is added to the websocket library
    server.addHandler(&ws); // the webserver will handle also the websocket

    pinMode(led, OUTPUT); // setting the led pin as output
    server.onNotFound(notFound); // default not found routine added to the not found exception
    server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}
