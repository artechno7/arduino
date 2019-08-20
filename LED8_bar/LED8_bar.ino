int numPins = 8;
int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
int ledStates[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

// Analog pin A0 is where you hook the potentiometer up. Or microphone. Or w/e.
int sensorPin = A0;
int sensorVal = 0;

void setup() {
  Serial.begin(9600);
  // set the digital pin as output:
  int i = 0;
  for(i = 0; i <= numPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop(){
  sensorVal = analogRead(sensorPin);
  sensorVal /= 100; // want this to be btn 0-10
  // arduino has a 10bit A->D converter. So divide 1024 by 100 gives us ~ 0-10 scale.
  Serial.println(sensorVal);
  int i = 0;
  for(i = 0; i <= numPins; i++) {
    if(sensorVal > i) {
      ledStates[i] = HIGH;
    }
    else {
      ledStates[i] = LOW;
    }
  digitalWrite(ledPins[i], ledStates[i]);
  }

} // End main loop
