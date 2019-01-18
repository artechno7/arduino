/* www.nyebarilmu.com */

#define kunci_B0  31
#define kunci_C1  33
#define kunci_CS1 35
#define kunci_D1  37
#define kunci_DS1 39
#define kunci_E1  41
#define kunci_F1  44
#define kunci_FS1 46
#define kunci_G1  49
#define kunci_GS1 52
#define kunci_A1  55
#define kunci_AS1 58
#define kunci_B1  62
#define kunci_C2  65
#define kunci_CS2 69
#define kunci_D2  73
#define kunci_DS2 78
#define kunci_E2  82
#define kunci_F2  87
#define kunci_FS2 93
#define kunci_G2  98
#define kunci_GS2 104
#define kunci_A2  110
#define kunci_AS2 117
#define kunci_B2  123
#define kunci_C3  131
#define kunci_CS3 139
#define kunci_D3  147
#define kunci_DS3 156
#define kunci_E3  165
#define kunci_F3  175
#define kunci_FS3 185
#define kunci_G3  196
#define kunci_GS3 208
#define kunci_A3  220
#define kunci_AS3 233
#define kunci_B3  247
#define kunci_C4  262
#define kunci_CS4 277
#define kunci_D4  294
#define kunci_DS4 311
#define kunci_E4  330
#define kunci_F4  349
#define kunci_FS4 370
#define kunci_G4  392
#define kunci_GS4 415
#define kunci_A4  440
#define kunci_AS4 466
#define kunci_B4  494
#define kunci_C5  523
#define kunci_CS5 554
#define kunci_D5  587
#define kunci_DS5 622
#define kunci_E5  659
#define kunci_F5  698
#define kunci_FS5 740
#define kunci_G5  784
#define kunci_GS5 831
#define kunci_A5  880
#define kunci_AS5 932
#define kunci_B5  988
#define kunci_C6  1047
#define kunci_CS6 1109
#define kunci_D6  1175
#define kunci_DS6 1245
#define kunci_E6  1319
#define kunci_F6  1397
#define kunci_FS6 1480
#define kunci_G6  1568
#define kunci_GS6 1661
#define kunci_A6  1760
#define kunci_AS6 1865
#define kunci_B6  1976
#define kunci_C7  2093
#define kunci_CS7 2217
#define kunci_D7  2349
#define kunci_DS7 2489
#define kunci_E7  2637
#define kunci_F7  2794
#define kunci_FS7 2960
#define kunci_G7  3136
#define kunci_GS7 3322
#define kunci_A7  3520
#define kunci_AS7 3729
#define kunci_B7  3951
#define kunci_C8  4186
#define kunci_CS8 4435
#define kunci_D8  4699
#define kunci_DS8 4978

#define melodyPin 10

//Mario main theme melody
int melody[] = {
  kunci_E7, kunci_E7, 0, kunci_E7,
  0, kunci_C7, kunci_E7, 0,
  kunci_G7, 0, 0,  0,
  kunci_G6, 0, 0, 0,

  kunci_C7, 0, 0, kunci_G6,
  0, 0, kunci_E6, 0,
  0, kunci_A6, 0, kunci_B6,
  0, kunci_AS6, kunci_A6, 0,

  kunci_G6, kunci_E7, kunci_G7,
  kunci_A7, 0, kunci_F7, kunci_G7,
  0, kunci_E7, 0, kunci_C7,
  kunci_D7, kunci_B6, 0, 0,

  kunci_C7, 0, 0, kunci_G6,
  0, 0, kunci_E6, 0,
  0, kunci_A6, 0, kunci_B6,
  0, kunci_AS6, kunci_A6, 0,

  kunci_G6, kunci_E7, kunci_G7,
  kunci_A7, 0, kunci_F7, kunci_G7,
  0, kunci_E7, 0, kunci_C7,
  kunci_D7, kunci_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

//Underworld melody
int underworld_melody[] = {
  kunci_C4, kunci_C5, kunci_A3, kunci_A4,
  kunci_AS3, kunci_AS4, 0,
  0,
  kunci_C4, kunci_C5, kunci_A3, kunci_A4,
  kunci_AS3, kunci_AS4, 0,
  0,
  kunci_F3, kunci_F4, kunci_D3, kunci_D4,
  kunci_DS3, kunci_DS4, 0,
  0,
  kunci_F3, kunci_F4, kunci_D3, kunci_D4,
  kunci_DS3, kunci_DS4, 0,
  0, kunci_DS4, kunci_CS4, kunci_D4,
  kunci_CS4, kunci_DS4,
  kunci_DS4, kunci_GS3,
  kunci_G3, kunci_CS4,
  kunci_C4, kunci_FS4, kunci_F4, kunci_E3, kunci_AS4, kunci_A4,
  kunci_GS4, kunci_DS4, kunci_B3,
  kunci_AS3, kunci_A3, kunci_GS3,
  0, 0, 0
};

//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

void setup(void)
{
  pinMode(10, OUTPUT);//buzzer
  pinMode(13, OUTPUT);//led indicator when singing a note

}
void loop()
{
  //sing the tunes
  sing(1);
  sing(1);
  sing(2);
}
int song = 0;

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];

      buzz(melodyPin, underworld_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }

  } else {

    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; // Menghitung nilai keterlambatan antara transisi
  //// 1 detik dari mikrodetik, dibagi dengan frekuensi, lalu dibagi dua sejak itu
  //// ada dua fase untuk setiap siklus
  long numCycles = frequency * length / 1000; // hitung jumlah siklus untuk timing yang tepat
  //// kalikan frekuensi, yang benar-benar siklus per detik, dengan jumlah detik untuk
  //// dapatkan jumlah total siklus yang akan dihasilkan
  for (long i = 0; i < numCycles; i++) { // untuk menghitung lamanya waktu ...
    digitalWrite(targetPin, HIGH); // tuliskan pin buzzer yang tinggi untuk mengeluarkan diafragma
    delayMicroseconds(delayValue); // tunggu nilai penundaan yang dihitung
    digitalWrite(targetPin, LOW); // Tuliskan pin buzzer yang rendah untuk menarik kembali diafragma
    delayMicroseconds(delayValue); // tunggu kembali atau nilai delay yang dihitung
  }
  digitalWrite(13, LOW);

}