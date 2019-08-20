#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//i2c lcd library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "Teknisi";
const char* password = "bondowoso";


void setup () {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  lcd.begin();
  Serial.println("==================================================");
  Serial.println("Hello World!");
  Serial.println("Setting NodeMCU");
  delay(1000);
  wifiConnecting();
}
 
void loop() {
  String url = "https://api.thingspeak.com/apps/thinghttp/send_request?api_key=UOGN6AALH8P3E8PO";
  if (WiFi.status() == WL_CONNECTED) { 
    HTTPClient http;  
    http.begin(url);  
    int httpCode = http.GET();                                                       
    if (httpCode > 0) { 
      String payload = http.getString();
      Serial.println("HTTP Response Code : ");
      Serial.println(httpCode);
      Serial.println("HTTP Response Payload : ");
      Serial.println(payload);
      lcd.print(payload);
    }
    http.end();   
  }else
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("NodeMCU tidak terhubung ke Access Point");
    wifiConnecting();
  }
  delay(5000);
}

void wifiConnecting(){
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Menghubungkan ke Access Point");
    for(int c=0;c<3;c++){
      Serial.print(" .");
      delay(1000);  
    }
    Serial.println();
  }
}
