#include "millisDelay.h" 
const int led = 5;
const int pb = 2;
int pb1;
millisDelay ledDelay;

void setup() {
  pinMode(pb, INPUT);
  pinMode(led, OUTPUT);   // initialize the digital pin as an output.
  digitalWrite(led, HIGH); // turn led on 
  digitalWrite(pb, LOW);

  //ledDelay.start(10000);  // start a 10sec delay
}

void loop() {
  pb1 = digitalRead(pb);

  if(pb1 == HIGH)
  {
    digitalWrite(led, LOW);
    ledDelay.start(10000);
  }
  // check if delay has timed out
  if (ledDelay.justFinished()) {
    digitalWrite(led, HIGH); // turn led off
    Serial.println("Turned LED Off");
  }
//  Other loop code here . . .
  Serial.println("Run Other Code");
}
