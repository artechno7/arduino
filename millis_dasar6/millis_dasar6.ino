#include <SimpleTimer.h>

int led1 = 2; 
int led2 = 3;
SimpleTimer timer;

char val="0";
void setup(){
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  Serial.begin(9600);
}

void loop(){
  timer.run();
  if(Serial.available()){
    val=Serial.read();
    Serial.println(val);
  }
  if(val=="1"){
    digitalWrite(led1,HIGH);
    timer.setTimeout(5000,pin2high);
  }

  else if(val="2"){
    digitalWrite(led2,HIGH);
  }
  
}

void pin2high(){
    digitalWrite(led1,HIGH);
    val="0";
  }
