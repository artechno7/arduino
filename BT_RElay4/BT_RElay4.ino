#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4, 5); // TX,RX
#define PIN_GETAR   7;
const int R1=9, R2=10, R3=11, R4=12;
char val;
String valGetar="0";
void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(R3,OUTPUT);
  pinMode(R4,OUTPUT);
  pinMode(PIN_GETAR,INPUT);
  
  
  
  off();
  
}


void off()
{
    digitalWrite(R1,HIGH);
    digitalWrite(R2,HIGH);
    digitalWrite(R3,HIGH);
    digitalWrite(R4,HIGH);
    
       
}


void loop() {
  if (digitalRead(PIN_GETAR)== LOW) {
     valGetar="1";
  } else {
    valGetar="0";
  }
  if (BTSerial.available()){
    val=BTSerial.read();
    Serial.println(val);
  }
  
  if( val == '1' ) {
    digitalWrite(R1,LOW);
    }

  
  else if( val == '2' ) { 
   digitalWrite(R2,LOW);
   
    }
   
  else if( val == '3' ) {
    digitalWrite(R3,LOW);
    
  }
   
  else if( val == '4' ) {
    digitalWrite(R4,LOW);
    
    }

 
 
  else if( val == 'A' ) {
    off(); 
    
    }
  else if( val == 'B' ) {
    off();   
    
    }
  else if( val == 'C' ) {
    off(); 
   
    }
  else if( val == 'D' ) {
    off(); }
  
}
