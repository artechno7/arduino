
#include <ESP8266WiFi.h>
#include <Wire.h>  // This library is already built in to the Arduino IDE
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library >  


 
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "Teknisi"; // put your router name
const char* password = "bondowoso";// put your password 
 
const char* host = "api.thingspeak.com";


int find_text(String needle, String haystack,int from) {
  int foundpos = -1;
  if (haystack.length()<needle.length())
    return foundpos;
  for (int i = from; (i < haystack.length() - needle.length()); i++) {
    if (haystack.substring(i,needle.length()+i) == needle) {
      foundpos = i;
      return foundpos;
    }
  }
  return foundpos;
}



 
void setup() {
  Serial.begin(115200);
  delay(100);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  delay(200);
   lcd.noBacklight();
   delay(200); 
    lcd.backlight(); // Enable or Turn On the backlight 
  delay(200);
   lcd.noBacklight();
   delay(200); 
    lcd.backlight(); // Enable or Turn On the backlight 
  delay(200);
 //  lcd.noBacklight();
   delay(200); 
 
 // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
int value = 0;




 
void loop() {
 
 
 
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
   
  }
  
  // We now create a URI for the request
  String url = "https://api.thingspeak.com/apps/thinghttp/send_request?api_key=UOGN6AALH8P3E8PO";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
   String line = client.readStringUntil('\r');
   

   

int start_loc= find_text("<b>",line,0);
int end_loc=find_text("</b>",line,0);
   lcd.setCursor();
if (start_loc>0 && end_loc>0)
{
  Serial.println("subs:  ");
  lcd.print("subs: ");
for (int i=start_loc+3;i<end_loc;i++)
{
Serial.print(line[i]);
 lcd.print(line[i]);
}
Serial.println("");
 lcd.setCursor(0, 1);
int start_loc2= find_text("<b>",line,end_loc+1);
int end_loc2=find_text("</b>",line,end_loc+1);
if (start_loc2>0 && end_loc2>0)
{
   lcd.print("views: ");
  Serial.println("views:");
for (int i=start_loc2+3;i<end_loc2;i++)
{
   lcd.print(line[i]);
Serial.print(line[i]);
}
}


}
    
 //   Serial.println(line);
  }
  
  Serial.println();
  Serial.println("closing connection");



  delay(2000);

   lcd.noBacklight();
   delay(1000); 
    lcd.backlight(); // Enable or Turn On the backlight 
  delay(800);
 
    lcd.noBacklight();
   delay(500); 
    lcd.backlight(); // Enable or Turn On the backlight 
  delay(400);

    lcd.noBacklight();
   delay(300); 
    lcd.backlight(); // Enable or Turn On the backlight 
  delay(150);
    lcd.noBacklight();
   delay(100); 
    lcd.backlight(); // Enable or Turn On the backlight 
  delay(100);
    lcd.noBacklight();
   delay(50); 
    lcd.backlight(); // Enable or Turn On the backlight 
  delay(50);
 
  
 
  
 
  
 
  
 
 
}
