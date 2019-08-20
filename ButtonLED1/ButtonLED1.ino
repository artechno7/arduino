int buttonPin = 2;     
int ledPin =  13;      

int buttonState = 0;      

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
 
  if (buttonState == HIGH) 
  {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
    Serial.println("TOMBOL ON");
  } 
  else 
  {
    digitalWrite(ledPin, LOW);
    Serial.println("TOMBOL OFF");
  }
}
