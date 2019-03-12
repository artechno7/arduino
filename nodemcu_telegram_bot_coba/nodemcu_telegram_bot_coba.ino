#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>
 
// Initialize Wifi connection to the router  
const char* ssid  = "Teknisi";
const char* password = "bondowoso";
 
// Initialize your Telegram BOT API  
const char BotToken[] = "639031750:AAGqPTEXO3Myc54WiPCSwUhD4KwkUyxlfr8";
 
WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);
 
const int ledPin = 16;  // the number of the LED pin 
 
void setup() 
{  
 Serial.begin(115200);  
 while (!Serial) {}  //Start running when the serial is open 
 delay(3000);  
 // attempt to connect to Wifi network:  
 Serial.print("Connecting Wifi: ");  
 Serial.println(ssid);  
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
 Serial.println("");  
 Serial.println("WiFi connected");  
 bot.begin();  
 pinMode(ledPin, OUTPUT);  
}  
 
void loop() 
{  
 message m = bot.getUpdates(); // Read new messages  
 if (m.text.equals("On")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(ledPin, HIGH);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led is now ON");  //Balasan dari perangkat ke Bot Telegram
 }  
 else if (m.text.equals("Off")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(ledPin, LOW);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led is now OFF");  //Balasan dari perangkat ke Bot Telegram
 }  
}
