#include <ESP8266WiFi.h>
#include <time.h>

//i2c lcd library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const char* ssid = "Teknisi";
const char* password = "bondowoso";

int ledPin = 13;

int timezone = 7 * 3600;
int dst = 0;

void setup() {
  

  Serial.begin(115200);
  lcd.begin();
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  configTime(timezone, dst, "id.pool.ntp.org","asia.pool.org");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK");   
  
}

void loop() {
  
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  Serial.print(p_tm->tm_mday);
  Serial.print("/");
  Serial.print(p_tm->tm_mon + 1);
  Serial.print("/");
  Serial.print(p_tm->tm_year + 1900);
  
  Serial.print(" ");
  
  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.print(p_tm->tm_sec);
  
  lcd.clear();
  lcd.print("   ");
  lcd.print(p_tm->tm_mday);
  lcd.print("/");
  lcd.print(p_tm->tm_mon + 1);
  lcd.print("/");
  lcd.print(p_tm->tm_year + 1900);
  
  lcd.print(" ");

  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.print(p_tm->tm_hour);
  lcd.print(":");
  lcd.print(p_tm->tm_min);
  lcd.print(":");
  lcd.print(p_tm->tm_sec);
  delay(1000);

}
