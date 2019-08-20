//#include <SoftwareSerial.h>

const int kontak1=2, kontak2=3, starter=4, rem=5, kiri=6, kanan=7, klakson=8, ext=9; //ext=external atau tambahan
char val;
void setup() {
  
  pinMode(kontak1,OUTPUT);
  pinMode(kontak2,OUTPUT);
  pinMode(starter,OUTPUT);
  pinMode(rem,OUTPUT);
  pinMode(kiri,OUTPUT);
  pinMode(kanan,OUTPUT);
  pinMode(klakson,OUTPUT);
  pinMode(ext,OUTPUT);
  off();

  Serial.begin(9600);
}


void off() //menonaktifkan relay dikasih high
{
    digitalWrite(kontak1,HIGH);
    digitalWrite(kontak2,HIGH);
    digitalWrite(starter,HIGH);
    digitalWrite(rem,HIGH);
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
    digitalWrite(kontak1,LOW);
    digitalWrite(kontak2,LOW);
    }
    
  else if( val == '2' ) { 
   digitalWrite(starter,LOW);
   digitalWrite(rem,LOW);
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
    digitalWrite(kontak1,HIGH);
    digitalWrite(kontak2,HIGH);
    }
  else if( val == 'B' ) {
    digitalWrite(starter,HIGH);  
    digitalWrite(rem,HIGH);
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
