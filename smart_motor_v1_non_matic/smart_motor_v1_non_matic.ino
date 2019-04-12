//#include <SoftwareSerial.h>

const int a=2, b=3, c=4, d=5, e=6, f=7, g=8, h=9;
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

void maju()
{
 digitalWrite(a,HIGH);
 digitalWrite(c,HIGH); 
}

/*
void mundur()
{
 digitalWrite(b,HIGH);
 digitalWrite(d,HIGH); 
}

void kanan()
{
 digitalWrite(a,HIGH);
 digitalWrite(d,HIGH); 
}

void kiri()

{
 digitalWrite(c,HIGH);
 digitalWrite(b,HIGH); 
}
void flskiri()
{
 digitalWrite(f,HIGH);delay(300);
 digitalWrite(f,LOW); 
}

void flskanan()
{
 digitalWrite(g,HIGH);delay(300);
 digitalWrite(g,LOW); 
}

void bel()
{
 digitalWrite(e,HIGH);delay(300);
 digitalWrite(e,LOW); 
}
*/

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
  //kunci kontak
  if( val == '1' ) {
    digitalWrite(a,LOW);}

  //starter  
  else if( val == '2' ) { 
   digitalWrite(b,LOW);
    }
  else if( val == '3' ) {
    digitalWrite(c,LOW);
  }
   // mundur(); }
  else if( val == '4' ) {
    digitalWrite(d,LOW);
    //kanan(); 
    }
  else if( val == '5' ) {
    digitalWrite(e,LOW);
    //bel(); 
    } 
  else if( val == '6' ) {
    digitalWrite(f,LOW);
    //flskiri(); 
    }
  else if( val == '7' ) {
    digitalWrite(g,LOW);
    //flskanan();  
 }
 
  else if( val == 'A' ) {
    off(); 
    }
  else if( val == 'B' ) {
    off();    
    }
  else if( val == 'C' ) {
    off(); }
  else if( val == 'D' ) {
    off(); }
  else if( val == 'E' ) {
    off(); }
  else if( val == 'F' ) {
    off(); }
  else if( val == 'G' ) {
    off();    
  }
}
