#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#define PIN_TX    2
#define PIN_RX    3

#define PIN_SW 4
#define STA 5

#define R1      6
#define R2      7
#define R3      8
#define R4      9


int val_STA;

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

  //nyalakan modul dgn GND
  pinMode(PIN_SW,OUTPUT);
  delay(3000);
  pinMode(PIN_SW,INPUT);



//detect STA
pinMode(STA,INPUT);
  
pinMode(R1, OUTPUT);
pinMode(R2, OUTPUT);
pinMode(R3, OUTPUT);
pinMode(R4, OUTPUT);
//tipe relay aktif low dimatikan
digitalWrite(R1, 1);
digitalWrite(R2, 1);
digitalWrite(R3, 1);
digitalWrite(R4, 1);

//menjaga agar switch selalu ON
val_STA = digitalRead(STA);
delay(2000);
if(val_STA == 0){
//nyalakan modul dgn GND
  pinMode(PIN_SW,OUTPUT);
  delay(3000);
  pinMode(PIN_SW,INPUT);
}

  //******** Initialize sim808 module *************
  while(!sim808.init()) {
      delay(1000);
      Serial.println("Sim808 init error");
  }
  delay(3000);
  Serial.println("SMS READY !!!");
//  if( sim808.attachGPS())
//    Serial.println("Open the GPS power success");
//  else
//    Serial.println("Open the GPS power failure");
 
}
void loop() {
  // put your main code here, to run repeatedly:
messageIndex = sim808.isSMSunread();

val_STA = digitalRead(STA);

if(val_STA == 0){
//nyalakan modul dgn GND
  pinMode(PIN_SW,OUTPUT);
  delay(3000);
  pinMode(PIN_SW,INPUT);
}


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
        sim808.sendSMS(phone,"Relay 1 ON");
        digitalWrite(R1, 0);
        Serial.println("R1 nyala");
      }
      else if ((pesan == "R1 OFF")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Relay 1 OFF");
        digitalWrite(R1, 1);
        Serial.println("R1 mati");      
      }
      else if ((pesan == "R2 ON")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Relay 2 ON");
        digitalWrite(R2, 0);
        Serial.println("R2 nyala");
      }
      else if ((pesan == "R2 OFF")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Relay 2 OFF");
        digitalWrite(R2, 1);
        Serial.println("R2 mati");      
      }
      else if ((pesan == "R3 ON")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Relay 3 ON");
        digitalWrite(R3, 0);
        Serial.println("R3 nyala");
      }
      else if ((pesan == "R3 OFF")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Relay 3 OFF");
        digitalWrite(R3, 1);
        Serial.println("R3 mati");      
      }
      else if ((pesan == "R4 ON")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Relay 4 ON");
        digitalWrite(R4, 0);
        Serial.println("R4 nyala");
      }
      else if ((pesan == "R4 OFF")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Relay 4 OFF");
        digitalWrite(R4, 1);
        Serial.println("R4 mati");      
      }
      else if ((pesan == "RALL ON")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Relay all ON");
        digitalWrite(R1, 0);
        digitalWrite(R2, 0);
        digitalWrite(R3, 0);
        digitalWrite(R4, 0);
        Serial.println("R All nyala");      
      }
      else if ((pesan == "RALL OFF")&&(no == "+6281258699449")){
        sim808.sendSMS(phone,"Relay all OFF");
        digitalWrite(R1, 1);
        digitalWrite(R2, 1);
        digitalWrite(R3, 1);
        digitalWrite(R4, 1);
        Serial.println("R All mati");      
      }
   
   }
}
