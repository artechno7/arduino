//#include <SoftwareSerial.h>

const int kontak=2, starter=3, kiri=4, kanan=5, klakson=6, ext1=7, ext2=8, ext3=9; //ext=external atau tambahan
char val;
void setup() {
  
  pinMode(kontak,OUTPUT);
  pinMode(starter,OUTPUT);
  pinMode(kiri,OUTPUT);
  pinMode(kanan,OUTPUT);
  pinMode(klakson,OUTPUT);
  pinMode(ext1,OUTPUT);
  pinMode(ext2,OUTPUT);
  pinMode(ext3,OUTPUT);
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
    digitalWrite(ext1,HIGH);
    digitalWrite(ext2,HIGH);
    digitalWrite(ext3,HIGH);
       
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
    digitalWrite(ext1,LOW);
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
    digitalWrite(ext1,HIGH);
    }
}
