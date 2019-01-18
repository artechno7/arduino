

/* www.nyebarilmu.com */

#include <LiquidCrystal.h> //mengincludekan library LCD

//untuk urutannya RS, E, 4, 5, 6, 7 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //pin yang disambungkan antara arduino dengan LCD

void setup() {
  lcd.clear();
//prosedur pemanggilan fungsi LCD 
  lcd.begin(16, 2); //16 = Baris, 2 = kolom
}

void loop() {
  lcd.setCursor(00, 00);//set pada baris 1 dan kolom 1
  lcd.print("SELAMAT DATANG");
  delay(1000);//waktu jeda 1 detik
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft(); 
    delay(250);
  }
delay (1000);
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayRight(); 
    delay(250);
  }
  delay (1000); //waktu jeda 1 detik
  lcd.setCursor(00, 1); //set pada baris 2 dan kolom 1
   lcd.print("SELAMAT BELAJAR"); 
  delay(1000);
  lcd.clear();
}

