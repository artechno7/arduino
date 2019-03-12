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
 
//const int ledPin = 16;  // the number of the LED pin 
const int output16 = 16;
const int output5 = 5;
const int output4 = 4;
const int output0 = 0;
const int output2 = 2;
const int output14 = 14;
const int output12 = 12;
const int output13 = 13;
const int output15 = 15;
//const int output3 = 3; //TX
//const int output1 = 1; //RX
const int output10 = 10;
const int output9 = 9;


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
 //pinMode(ledPin, OUTPUT);  
 off();
  pinMode(output16, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output0, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output12, OUTPUT);
 pinMode(output13, OUTPUT);
  pinMode(output15, OUTPUT);
  //pinMode(output3, OUTPUT);
 // pinMode(output1, OUTPUT);
  pinMode(output10, OUTPUT);
  pinMode(output9, OUTPUT);
 
}  
 
void loop() 
{  
 message m = bot.getUpdates(); // Read new messages  
 if (m.text.equals("L1On")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(output16, LOW);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led1 is now ON");  //Balasan dari perangkat ke Bot Telegram
 }  
 else if (m.text.equals("L1Off")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(output16, HIGH);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led1 is now OFF");  //Balasan dari perangkat ke Bot Telegram
 }  

if (m.text.equals("L2On")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(output5, LOW);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led2 is now ON");  //Balasan dari perangkat ke Bot Telegram
 }  
 else if (m.text.equals("L2Off")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(output5, HIGH);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led2 is now OFF");  //Balasan dari perangkat ke Bot Telegram
 }  

 if (m.text.equals("L3On")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(output4, LOW);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led3 is now ON");  //Balasan dari perangkat ke Bot Telegram
 }  
 else if (m.text.equals("L3Off")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(output4, HIGH);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led3 is now OFF");  //Balasan dari perangkat ke Bot Telegram
 }  

 if (m.text.equals("L4On")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(output0, LOW);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led4 is now ON");  //Balasan dari perangkat ke Bot Telegram
 }  
 else if (m.text.equals("L4Off")) //Perintah dari telegram ke perangkat
       {  
   digitalWrite(output0, HIGH);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led4 is now OFF");  //Balasan dari perangkat ke Bot Telegram
 }  
 
}

void off()
{
  //relay off active low
  digitalWrite(output16, HIGH);
  digitalWrite(output5, HIGH);
  digitalWrite(output4, HIGH);
  digitalWrite(output0, HIGH);
  digitalWrite(output2, HIGH);
  digitalWrite(output14, HIGH);
  digitalWrite(output12, HIGH);
 digitalWrite(output13, HIGH);
  digitalWrite(output15, HIGH);
 // digitalWrite(output3, HIGH);
  //digitalWrite(output1, HIGH);
  digitalWrite(output10, HIGH);
  digitalWrite(output9, HIGH);
}
