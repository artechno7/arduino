//#include <SoftwareSerial.h>

const int a=12, b=11, c=10, d=9, e=8, f=7, g=6, h=5;
//a Kunci kontak on (relay utama dan display)
//b
char val;
void setup() {
  
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  pinMode(h,OUTPUT);
  
  off();
  Serial.begin(9600);
}


void off()
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
    digitalWrite(h,HIGH);
       
}


void loop() {
if( Serial.available() >0 ) {
    val = Serial.read();
    Serial.println(val); 
}
  
  if( val == '1' ) { 
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    }
    
  else if( val == '2' ) { 
   digitalWrite(c,LOW);
   digitalWrite(d,LOW);
    }
  else if( val == '3' ) { 
    digitalWrite(e,LOW);
  }
  else if( val == '4' ) {
    digitalWrite(e,LOW);
    digitalWrite(f,LOW); 
    }
  else if( val == '5' ) {
    digitalWrite(f,LOW);
    //bel(); 
    } 
  else if( val == '6' ) {
    digitalWrite(g,LOW);
    //flskiri(); 
    } 
 
 
  else if( val == 'A' ) {
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH); 
    }
  else if( val == 'B' ) {
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);    
    }
  else if( val == 'C' ) {
    digitalWrite(e,HIGH); 
   //off();
    }
  else if( val == 'D' ) {
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
   // off();
    }
  else if( val == 'E' ) {
    digitalWrite(f,HIGH); 
    //off();
    }
  else if( val == 'F' ) {
    digitalWrite(g,HIGH);
    //off();
    }
}
