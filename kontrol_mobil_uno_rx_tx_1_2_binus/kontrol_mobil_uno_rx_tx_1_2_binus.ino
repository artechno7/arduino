//#include <SoftwareSerial.h>

const int a=13, b=12, c=11, d=10, e=9, f=8, g=7;  //a,b,c,d data kontrol motor   e,f,g  = flash & bel
char val;
void setup() {
  
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);.
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);
  
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  
  Serial.begin(9600);
}

void maju()
{
 digitalWrite(a,HIGH);
 digitalWrite(c,HIGH); 
}

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

void off()
{
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
       
}


void loop() {
if( Serial.available() >0 ) {
    val = Serial.read();
    Serial.println(val); 
}
  if( val == '1' ) {
    maju(); }
  else if( val == '2' ) {
    kiri(); }
  else if( val == '3' ) {
    mundur(); }
  else if( val == '4' ) {
    kanan(); }
  else if( val == '5' ) {
    bel(); } 
  else if( val == '6' ) {
    flskiri(); }
  else if( val == '7' ) {
    flskanan();  
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
