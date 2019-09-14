#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#define PIN_TX    2
#define PIN_RX    3

#define PIN_TX_BT 4
#define PIN_RX_BT 5

#define PIN_KEY 6

#define PIN_VIBRA 7

#define R1      9
#define R2      10
#define R3      11
#define R4      12

SoftwareSerial mySerial(PIN_TX,PIN_RX);
//SoftwareSerial btSerial(PIN_TX_BT,PIN_RX_BT);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,
#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
int messageIndex = 0;
char phone[16];
char datetime[24];
void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  //btSerial.begin(9600);
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

//pin key diberi GND 3 detik untuk nyala
//pinMode(PIN_KEY,OUTPUT);
//delay(3000);
//pinMode(PIN_KEY,INPUT);

pinMode(PIN_VIBRA,INPUT);
 

  //******** Initialize sim808 module *************
  while(!sim808.init()) {
      delay(1000);
      Serial.println("Sim808 init error");
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
