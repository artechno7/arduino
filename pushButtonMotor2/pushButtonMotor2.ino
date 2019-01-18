#include <SoftwareSerial.h>
SoftwareSerial MySerial(12,13);//TX,RX
char tombol;
//int flag=0;

void setup()
{
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
MySerial.begin(9600);
}

void maju()
{
  digitalWrite(5,HIGH);
  digitalWrite(3,HIGH);
}

void mundur()
{
  digitalWrite(4,HIGH);
  digitalWrite(2,HIGH);
}

void kanan()
{
  digitalWrite(5,HIGH);
  digitalWrite(2,HIGH);
}

void kiri()
{
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
}
void flaskanan()
{
  digitalWrite(6,HIGH);delay(300);
  digitalWrite(6,LOW);
}
void flaskiri()
{
  digitalWrite(7,HIGH);delay(300);
  digitalWrite(7,LOW);
}
void buzzer()
{
  digitalWrite(9,HIGH);delay(300);
  digitalWrite(9,LOW);
}
void off(){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  }


void loop()
{
  if(MySerial.available()> 0)
  {
    tombol =MySerial.read();
    MySerial.println(tombol);
    //flag=0;
    
    }
    if (tombol==  '1'){
      maju();}
      else if (tombol==  '2'){
      kiri();}
      else if (tombol==  '3'){
      mundur();}
      else if (tombol==  '4'){
      kanan();}
      else if (tombol==  '5'){
      buzzer();}
      else if (tombol==  '6'){
      flaskiri();}
      else if (tombol==  '7'){
      flaskanan();}
      else if (tombol==  'A'){
      off();}
       else if (tombol==  'B'){
      off();}
       else if (tombol==  'C'){
      off();}
       else if (tombol==  'D'){
      off();}
       else if (tombol==  'E'){
      off();}
       else if (tombol==  'F'){
      off();}
       else if (tombol==  'G'){
      off();}
}

