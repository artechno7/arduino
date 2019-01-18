int led = 3; //Led pada pin 3
int i;  //menyimpan informasi untuk perulangan

void setup() {
  pinMode(led, OUTPUT); //pin mode output
}

void loop() {
  for (i = 0; i < 255; i++) //nilai i berubah dari 0 hingga 254
  {
    analogWrite(led, i); //led menyala perlahan
    delay(10);
  }
  for (i = 255; i > 0; i--) //nilai i berubah dari 255 hingga 0
  {
    analogWrite(led, i); //led redup perlahan
    delay(10);
  }
}

