const int pinLED1 = 12;
const int pinLED2 = 11;
const int pinLED3= 10;
const int pinLED4 = 9;
const int pinLED5 = 8;
const int pinLED6 = 7;
const int pinLED7 = 6;
const int pinLED8 = 5;
const int pinLED9 = 4;
const int pinLED10 = 3;
const int pinLED11 = 2;


void setup() {

pinMode(pinLED1, OUTPUT);
pinMode(pinLED2, OUTPUT);
pinMode(pinLED3, OUTPUT);
pinMode(pinLED4, OUTPUT);
pinMode(pinLED5, OUTPUT);
pinMode(pinLED6, OUTPUT);
pinMode(pinLED7, OUTPUT);
pinMode(pinLED8, OUTPUT);
pinMode(pinLED9, OUTPUT);
pinMode(pinLED10, OUTPUT);
pinMode(pinLED11, OUTPUT);

}

void loop() {

digitalWrite(pinLED1, HIGH);
digitalWrite(pinLED2, HIGH);
digitalWrite(pinLED3, HIGH);
digitalWrite(pinLED4, HIGH);
digitalWrite(pinLED5, HIGH);
digitalWrite(pinLED6, HIGH);
digitalWrite(pinLED7, HIGH);
digitalWrite(pinLED8, HIGH);
digitalWrite(pinLED9, HIGH);
digitalWrite(pinLED10, HIGH);
digitalWrite(pinLED11, HIGH);


delay(1000);

digitalWrite(pinLED1, LOW);
digitalWrite(pinLED2, LOW);
digitalWrite(pinLED3, LOW);
digitalWrite(pinLED4, LOW);
digitalWrite(pinLED5, LOW);
digitalWrite(pinLED6, LOW);
digitalWrite(pinLED7, LOW);
digitalWrite(pinLED8, LOW);
digitalWrite(pinLED9, LOW);
digitalWrite(pinLED10, LOW);
digitalWrite(pinLED11, LOW);

delay(1000);

}
