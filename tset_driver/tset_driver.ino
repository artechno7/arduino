int kirimaju = 2;
int kirimundur = 3;
int kananmaju = 4;
int kananmundur = 5;

void setup() {
  // put your setup code here, to run once:
pinMode(kirimaju,OUTPUT);
pinMode(kirimundur,OUTPUT);
pinMode(kananmaju,OUTPUT);
pinMode(kananmundur,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(kirimaju,1);
delay(3000);
digitalWrite(kirimaju,0);
delay(3000);
digitalWrite(kirimundur,1);
delay(3000);
digitalWrite(kirimundur,0);
delay(3000);
digitalWrite(kananmaju,1);
delay(3000);
digitalWrite(kananmaju,0);
delay(3000);
digitalWrite(kananmundur,1);
delay(3000);
digitalWrite(kananmundur,0);
delay(3000);
}
