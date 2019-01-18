#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;
String url; // string untuk menampung url
float suhu;

String api = "BB4D0DXBZ4T51FIX"; // kode API ThingSpeak Kalian (PERLU DISESUAIKAN)

void setup() {

    Serial.begin(115200); // memulai koneksi serial dgn boudrate 115200
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("Teknisi", "bondowoso"); // nama SSID dan Passwordnya (PERLU DISESUAIKAN)
}

void loop() 
  {
    while (WiFiMulti.run() != WL_CONNECTED) 
      {
          Serial.println("Connecting to Wi-Fi . .");
          delay(500);
      };
    
          //suhu = analogRead(A0)/9.31;       // memasukan data suhu ke variabel String h
          suhu = ( (analogRead(A0)/310.3) - 0.5) / 0.01 ;
    
    if((WiFiMulti.run() == WL_CONNECTED)) 
        {
          HTTPClient http;
          Serial.println("[HTTP] Memulai Koneksi...");

          url = "http://api.thingspeak.com/update?api_key=";
          url += api;
          url += "&field1=";
          url += String(suhu);

  
          Serial.println(url);
          http.begin(url); //HTTP Request ke URL
  
          int httpCode = http.GET(); // mengakses jawaban server
  
          if(httpCode > 0) {
               Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  
              if(httpCode == HTTP_CODE_OK) {
                  String payload = http.getString(); 
                  Serial.println(payload); // print balasan / file html dari server
                  Serial.println("\n\n");
              }
          } else {
              Serial.println("[HTTP] GET... failed");
          }
  
          http.end(); // mengakhiri Request
      }
  
      delay(10000); // jeda per koneksi 10 detik
  }
