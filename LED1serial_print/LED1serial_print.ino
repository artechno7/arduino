void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("LAMPU HIDUP");
  delay(2000);                       // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("LAMPU MATI");
  delay(2000);                       // wait for a second
  analogWrite(5,64);
}
