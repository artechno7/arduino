/*
### Read SMS messages
 1. This example is used to test DFRobot_SIM808 GPS/GPRS/GSM Shield's reading SMS
 2. Open the SIM808_SMSread example or copy these code to your project
 3. Download and dial the function switch to Arduino
 4. it will receive SMS Messages and send it to serial

create on 2016/09/23, version: 1.0
by jason
*/

#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
int messageIndex = 0;

char phone[16];
char datetime[24];

#define PIN_TX    2
#define PIN_RX    3

#define R1      9
#define R2      10
#define R3      11
#define R4      12

SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

//DFRobot_SIM808 sim808(&Serial);

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);

pinMode(R1, OUTPUT);
pinMode(R2, OUTPUT);
pinMode(R3, OUTPUT);
pinMode(R4, OUTPUT);
//tipe relay aktif low dimatikan
digitalWrite(R1, 1);
digitalWrite(R2, 1);
digitalWrite(R3, 1);
digitalWrite(R4, 1);

  //******** Initialize sim808 module *************
  while(!sim808.init()) {
      Serial.print("Sim808 init error\r\n");
      delay(1000);
  }
  delay(3000);  
  Serial.println("Init Success, please send SMS message to me!");
}

void loop() {
  //*********** Detecting unread SMS ************************
   messageIndex = sim808.isSMSunread();
    Serial.print("messageIndex: ");
    Serial.println(messageIndex);

   //*********** At least, there is one UNREAD SMS ***********
   if (messageIndex > 0) { 
      sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);
                 
      //***********In order not to full SIM Memory, is better to delete it**********
      sim808.deleteSMS(messageIndex);
      Serial.print("From number: ");
      Serial.println(phone);  
      Serial.print("Datetime: ");
      Serial.println(datetime);        
      Serial.print("Recieved Message: ");
      Serial.println(message); 
      String no = phone;
      String pesan = message;
      if ((pesan == "R1 ON")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Siap bos relay 1 sudah nyala, santai nomer lain gak bisa ngontrol");
        digitalWrite(R1, 0);
        Serial.println("RELAY 1 nyala");
      }
      else if ((pesan == "R1 OFF")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Siap bos relay 1 sudah mati, santai nomer lain gak bisa ngontrol");
        digitalWrite(R1, 1);
        Serial.println("RELAY 1 mati");      
      }
      else if ((pesan == "R2 ON")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Siap bos relay 2 sudah nyala, santai nomer lain gak bisa ngontrol");
        digitalWrite(R2, 0);
        Serial.println("RELAY 2 nyala");
      }
      else if ((pesan == "R2 OFF")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Siap bos relay 2 sudah mati, santai nomer lain gak bisa ngontrol");
        digitalWrite(R2, 1);
        Serial.println("RELAY 2 mati");      
      }
      else if ((pesan == "R3 ON")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Siap bos relay 3 sudah nyala, santai nomer lain gak bisa ngontrol");
        digitalWrite(R3, 0);
        Serial.println("RELAY 3 nyala");
      }
      else if ((pesan == "R3 OFF")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Siap bos relay 3 sudah mati, santai nomer lain gak bisa ngontrol");
        digitalWrite(R3, 1);
        Serial.println("RELAY 3 mati");      
      }
      else if ((pesan == "R4 ON")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Siap bos relay 4 sudah nyala, santai nomer lain gak bisa ngontrol");
        digitalWrite(R4, 0);
        Serial.println("RELAY 4 nyala");
      }
      else if ((pesan == "R4 OFF")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Siap bos relay 4 sudah mati, santai nomer lain gak bisa ngontrol");
        digitalWrite(R4, 1);
        Serial.println("RELAY 4 mati");      
      }   
   }
}
