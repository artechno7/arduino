int ledPin = 5;    // LED di pin 9

void setup() {
  Serial.begin(9600);
}

void loop() {
   analogWrite(ledPin, 255); // LED nyala sempurna
   Serial.println("pwm 255");
   delay(3000);
   analogWrite(ledPin, 128); //LED setengah redup
   Serial.println("pwm 128");
   delay(3000);
   analogWrite(ledPin, 0); //LED mati
   Serial.println("pwm 0");
   delay(3000);
}
