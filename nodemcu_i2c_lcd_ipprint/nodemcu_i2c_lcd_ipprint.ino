/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>

//i2c lcd library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
// Replace with your network credentials
const char* ssid     = "Teknisi";
const char* password = "bondowoso";


void setup() {
  Serial.begin(9600);
// initial lcd
lcd.begin();
lcd.print("Welcome..");
lcd.setCursor(0,1);
lcd.print("NodeMCU ESP8266");
delay(2000);
  
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //lcd write
  lcd.clear();
  lcd.print("WiFi connected. ");
  delay(1000);
  lcd.clear();
  lcd.print("IP address: ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  
}

void loop(){
  
}
