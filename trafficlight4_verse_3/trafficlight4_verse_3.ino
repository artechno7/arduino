void setup() {
pinMode(0,OUTPUT);
pinMode(1,OUTPUT);
pinMode(2,OUTPUT);
}

void loop() {
digitalWrite(0,HIGH);
digitalWrite(1,LOW);
digitalWrite(2,LOW);
delay(7000);
digitalWrite(0,LOW);
digitalWrite(1,HIGH);
digitalWrite(2,LOW);
delay(1000);
digitalWrite(0,LOW);
digitalWrite(1,LOW);
digitalWrite(2,HIGH);
delay(7000);
digitalWrite(0,LOW);
digitalWrite(1,HIGH);
digitalWrite(2,LOW);
delay(1000);



}
