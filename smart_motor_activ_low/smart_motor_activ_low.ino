//#include <SoftwareSerial.h>

const int kontak=12, starter=11, kiri=10, kanan=9, klakson=8, ext=7;
char val;
void setup() {
  
  pinMode(kontak,OUTPUT);
  pinMode(starter,OUTPUT);
  pinMode(kiri,OUTPUT);
  pinMode(kanan,OUTPUT);
  pinMode(klakson,OUTPUT);
  pinMode(ext,OUTPUT);
  off();

  Serial.begin(9600);
}


void off()
{
    digitalWrite(kontak,HIGH);
    digitalWrite(starter,HIGH);
    digitalWrite(kiri,HIGH);
    digitalWrite(kanan,HIGH);
    digitalWrite(klakson,HIGH);
    digitalWrite(ext,HIGH);
       
}


void loop() {
if( Serial.available() >0 ) {
    val = Serial.read();
    Serial.println(val); 
}
//if( BTSerial.available() >0 ) {
//    val = BTSerial.read();
//    Serial.println(val); 
//}
  if( val == '1' ) { 
    digitalWrite(kontak,LOW);
    }
    
  else if( val == '2' ) { 
   digitalWrite(starter,LOW);
    }
  else if( val == '3' ) { 
    digitalWrite(kiri,LOW);
  }
  else if( val == '4' ) {
    digitalWrite(kiri,LOW);
    digitalWrite(kanan,LOW); 
    }
  else if( val == '5' ) {
    digitalWrite(kanan,LOW); 
    } 
  else if( val == '6' ) {
    digitalWrite(ext,LOW);
    } 
 
 
  else if( val == 'A' ) {
    digitalWrite(kontak,HIGH);
    }
  else if( val == 'B' ) {
    digitalWrite(starter,HIGH);  
    }
  else if( val == 'C' ) {
    digitalWrite(kiri,HIGH);
    }
  else if( val == 'D' ) {
    digitalWrite(kiri,HIGH);
    digitalWrite(kanan,HIGH); 
    }
  else if( val == 'E' ) {
    digitalWrite(kanan,HIGH); 
    }
  else if( val == 'F' ) {
    digitalWrite(ext,HIGH);
    }
}
