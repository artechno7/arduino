int led1 = 2;
int led2 = 3;

void setup() {
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
}
  
void loop() {
   digitalWrite(led1, HIGH);   // set the LED on
   for (int x=0; x < 1000; x++) {             // loop selama satu detik ( x counting 1 )
      delay(1);
      if (x==500) {
         digitalWrite(led2, HIGH); // hidupkan ketika x berjumlah 500
      }
   }
   digitalWrite(led1, LOW);    // set LED padam
   for (int x=0; x < 1000; x++) {             // tunggu selama satu detik
      delay(1);
      if (x==500) {
            digitalWrite(led2, LOW); // padamkan Led jika x = 500
      }
   }
}
