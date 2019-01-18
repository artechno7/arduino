/* www.nyebarilmu.com */
//lagu happy birthday

//deklarasi variabel data
int pin10 = 10;
int pin13 = 13;
int panjang = 28; //jumalh dari nada
int ketukan[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8,8, 16, 1, 2,2,8,8,8,8,16, 1,2,2,8,8,8,16 };
char kunci[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int tempo_kecepatan = 150;

//Fungsi playTone
void playTone(int nada, int durasi) {
for (long i = 0; i < durasi * 1000L; i += nada * 2) {
   digitalWrite(pin10, HIGH);
   delayMicroseconds(nada);
   digitalWrite(pin10, LOW);
   delayMicroseconds(nada);
}}

//Fungsi playNote
void playNote(char note, int duration) {
char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           
                 'c', 'd', 'e', 'f', 'g', 'a', 'b',
                 'x', 'y' };

int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,
                 956,  834,  765,  593,  468,  346,  224,
                 655 , 715 };

int SPEE = 5;
// play the tone corresponding to the note name
for (int i = 0; i < 17; i++) {
   if (names[i] == note) {
    int newduration = duration/SPEE;
     playTone(tones[i], newduration);
   }
}}

void setup() {
pinMode(pin13, OUTPUT);
}

void loop() {
for (int i = 0; i < panjang; i++) {
   if (ketukan[i] == ' ') {
     delay(nada[i] * tempo_kecepatan); // rest
   } else {
     playNote(ketukan[i], nada[i] * tempo_kecepatan);
   }
   // pause between ketukan
   delay(tempo_kecepatan);
}}
