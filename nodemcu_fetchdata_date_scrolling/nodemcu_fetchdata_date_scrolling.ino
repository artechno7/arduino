/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

//i2c lcd library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {

  USE_SERIAL.begin(115200);
  // USE_SERIAL.setDebugOutput(true);
lcd.begin();
//  USE_SERIAL.println();
//  USE_SERIAL.println();
//  USE_SERIAL.println();

//  for (uint8_t t = 4; t > 0; t--) {
//    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
//    USE_SERIAL.flush();
//    delay(1000);
//  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Teknisi", "bondowoso");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

  // USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
   http.begin("api.thingspeak.com", 80, "/apps/thinghttp/send_request?api_key=R7AO0TPVSGO5APBE"); //HTTP

  // USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
  if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
    // USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
     if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.print(payload);
        lcd.clear();
        String dateku = payload.substring(0,20);
        lcd.setCursor(0,1);
        lcd.print(" " + dateku);
        for (int i=1; i<23; i++){
        lcd.scrollDisplayLeft();
        delay(300);
        

        
        }

        
      }
    
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
   }

   http.end();
 }
  
  //delay(500);
  }
