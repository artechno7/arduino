#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#define PIN_TX    2
#define PIN_RX    3
SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,
#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
int messageIndex = 0;
char phone[16];
char datetime[24];
void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);
pinMode(7, OUTPUT);
pinMode(6, OUTPUT);
digitalWrite(6, 1);
digitalWrite(7, 1);
  //******** Initialize sim808 module *************
  while(!sim808.init()) {
      delay(1000);
      Serial.println("Sim808 init errorrn");
  }
  delay(3000);
  Serial.println("SMS READY !!!");
  if( sim808.attachGPS())
      Serial.println("Open the GPS power success");
  else
      Serial.println("Open the GPS power failure");
 
}
void loop() {
  // put your main code here, to run repeatedly:
messageIndex = sim808.isSMSunread();
if (messageIndex > 0) {
      sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);
    
      sim808.deleteSMS(messageIndex);
      Serial.print("From number: ");
      Serial.println(phone); 
      Serial.print("Datetime: ");
      Serial.println(datetime);       
      Serial.print("Recieved Message: ");
      Serial.println(message);
      String no = phone;
      String pesan = message;
      if ((pesan == "Led1 nyala")&&(no == "+6285780391803")){
        sim808.sendSMS(phone,"Siap bos led1 udah nyalan santai nomer lain gak bisa ngontrol");
        digitalWrite(7, 0);
        digitalWrite(6, 1);
        Serial.println("Led 1 nyala");
      }
      else if ((pesan == "Led1 mati")&&(no == "+6285780391803")){
        sim808.sendSMS(phone,"Siap bos led1 udah matin santai nomer lain gak bisa ngontrol");
        digitalWrite(7, 1);
        digitalWrite(6, 1); 
        Serial.println("Led2 mati");      
      }
      else {
        digitalWrite(6, 0);
      }
   }
}
