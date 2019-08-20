// PROJECT: Toggle On/Off LED dan Pushbutton
// Level: 1/10

const int LED = 2; // pin untuk LED
const int BUTTON = 10; // pin untuk pushbutton
int val = 0; // variabel penyimpan nilai input
int old_val = 0; // variabel untuk menyimpan nilai input sebelumnya
int state = 0; // 0 = LED off dan 1 = LED on

void setup() {
   pinMode(LED, OUTPUT); // deklarasi LED sbg output
   pinMode(BUTTON, INPUT); // deklarasi pushbutton sbg input
}

void loop(){
   val = digitalRead(BUTTON); // membaca nilai BUTTON menyimpan nilainya
   // mengecek perubahan val
   if ((val == HIGH) && (old_val == LOW)){
      state = 1 - state;
      delay(10); //proses debouncing, untuk mencegah kesalahan baca
   }
   old_val = val;
   if (state == 1) {
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
   } else {
      digitalWrite(LED, LOW);
   }
}
