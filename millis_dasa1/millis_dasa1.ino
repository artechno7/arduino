void setup() {
   pinMode(13, OUTPUT);
}
  
void loop() {
   digitalWrite(13, HIGH);   // set the LED on
   for (int x=0; x < 1000; x++) {     // tunggu selama satu detik
      delay(1);
   }
   digitalWrite(13, LOW);   // set the LED on
   for (int x=0; x < 1000; x++) {     // tunggu selama satu detik
      delay(1);
   }
}
