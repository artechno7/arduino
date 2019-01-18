//Code written by Samuel.

int buzzerPin = 3; //Define buzzerPin

void setup() {
  pinMode(buzzerPin, OUTPUT); //Set buzzerPin as output
  beep(100); //Beep
  beep(100); //Beep
  delay(1000); //Add a little delay

}

void loop() {
  beep(500); //Beep every 500 milliseconds
  //delay(500);
}

void beep(unsigned char delayms) { //creating function
  analogWrite(buzzerPin, 1000); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
  analogWrite(buzzerPin, 100); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
}
