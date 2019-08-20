

/* www.nyebarilmu.com */

#include <LiquidCrystal.h> //mengincludekan library LCD

//untuk urutannya RS, E, 4, 5, 6, 7 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //pin yang disambungkan antara arduino dengan LCD


void setup() {
  lcd.clear();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("SELAMAT DATANG");
  delay(1000);
}

void loop() {

  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // bergerak ke arah kiri:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  // delay at the end of the full loop:
    lcd.autoscroll();
  delay(100);


}
