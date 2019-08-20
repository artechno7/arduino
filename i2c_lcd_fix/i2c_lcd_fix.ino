#include <Wire.h>  // i2C Conection Library
#include <LiquidCrystal_I2C.h>  //Memanggil i2C LCD Library

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
 lcd.begin();
 lcd.setCursor (0,0);
  lcd.print(F("  Excellent  "));
  lcd.setCursor (0,1);
  lcd.print(F(" 8Channel Relay "));
  //delay (2000);
  //lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:

}
