int g1 = 2;
int y1 = 3; 
int r1 = 4;
int g2 = 5;
int y2 = 6;
int r2 = 7;
int g3 = 8;
int y3 = 9;
int r3 = 10;
int g4 = 11;
int y4 = 12;
int r4 = 13;

void setup() {
  // put your setup code here, to run once:
pinMode (r1, OUTPUT);
pinMode (y1, OUTPUT);
pinMode (g1, OUTPUT);
pinMode (r2, OUTPUT);
pinMode (y2, OUTPUT);
pinMode (g2, OUTPUT);
pinMode (r3, OUTPUT);
pinMode (y3, OUTPUT);
pinMode (g3, OUTPUT);
pinMode (r4, OUTPUT);
pinMode (y4, OUTPUT);
pinMode (g4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
// PATTERN 1 AND 2
    
digitalWrite(g1,HIGH);
digitalWrite(r2,HIGH);
digitalWrite(r3,HIGH);
digitalWrite(r4,HIGH);
delay(10000);

digitalWrite(g1,LOW);

digitalWrite(y1,HIGH);
digitalWrite(r2,HIGH);
digitalWrite(r3,HIGH);
digitalWrite(r4,HIGH);
delay(3000);

digitalWrite(y1,LOW);
digitalWrite(r2,LOW);

digitalWrite(r1,HIGH);
digitalWrite(g2,HIGH); //2nd light
digitalWrite(r3,HIGH);
digitalWrite(r4,HIGH);
delay(10000);

digitalWrite(g2,LOW);

digitalWrite(y2,HIGH);
digitalWrite(r1,HIGH);
digitalWrite(r3,HIGH);
digitalWrite(r4,HIGH);
delay(3000);

digitalWrite(y2,LOW);
digitalWrite(r3,LOW);

digitalWrite(g3,HIGH);//3rd light
digitalWrite(r1,HIGH);
digitalWrite(r2,HIGH);
digitalWrite(r4,HIGH);
delay(10000);

digitalWrite(g3,LOW);


digitalWrite(y3,HIGH);
digitalWrite(r1,HIGH);
digitalWrite(r2,HIGH);
digitalWrite(r4,HIGH);
delay(3000);

digitalWrite(y3,LOW);
digitalWrite(r3,LOW);
digitalWrite(r4,LOW);

digitalWrite(g4,HIGH);//4th light
digitalWrite(r1,HIGH);
digitalWrite(r2,HIGH);
digitalWrite(r3,HIGH);
delay(10000);

digitalWrite(g4,LOW);
digitalWrite(r4,LOW);


digitalWrite(y4,HIGH);
digitalWrite(r1,HIGH);
digitalWrite(r2,HIGH);
digitalWrite(r3,HIGH);
delay(3000);

digitalWrite(y4,LOW);
digitalWrite(r4,LOW);
digitalWrite(r1,LOW);

}
