//rOBOT REMOTE BLUETOOTH 05

//#include <SoftwareSerial.h> //wajib pake kalau pin bluetooth tidak di 0 dan 1

//PIN BLUETOOTH RX,TX,0,1
//our L298N control pins
const int LeftMotorForward = 2;
const int LeftMotorBackward = 3;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

const int e=9, f=8, g=7; //   e = bel, f,g  = flash & bel
char val;
void setup() {
  
  // Set L298N Control Pins as Output
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  pinMode(e,OUTPUT);
  pinMode(f,OUTPUT);
  pinMode(g,OUTPUT);
  
  Serial.begin(9600);
}

void maju()
{
 digitalWrite(RightMotorForward, HIGH);
 digitalWrite(RightMotorBackward, LOW);
 digitalWrite(LeftMotorForward, HIGH);
 digitalWrite(LeftMotorBackward, LOW);
}

void mundur()
{
 digitalWrite(RightMotorForward, LOW);
 digitalWrite(RightMotorBackward, HIGH);
 digitalWrite(LeftMotorForward, LOW);
 digitalWrite(LeftMotorBackward, HIGH);
}

void kanan()
{
 digitalWrite(RightMotorForward, LOW);
 digitalWrite(RightMotorBackward, HIGH);
 digitalWrite(LeftMotorForward, HIGH);
 digitalWrite(LeftMotorBackward, LOW);
}

void kiri()

{
 digitalWrite(RightMotorForward, HIGH);
 digitalWrite(RightMotorBackward, LOW);
 digitalWrite(LeftMotorForward, LOW);
 digitalWrite(LeftMotorBackward, HIGH); 
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
    digitalWrite(RightMotorForward,LOW);
    digitalWrite(RightMotorBackward,LOW);
    digitalWrite(LeftMotorForward,LOW);
    digitalWrite(LeftMotorBackward,LOW);
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
