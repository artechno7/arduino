#include <Wire.h>  // i2C Conection Library
#include <LiquidCrystal_I2C.h>  //i2C LCD Library

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
 // initialize the LCD
 lcd.begin();

  lcd.print("Hello, world!");
  delay (1000);

  lcd.setCursor(0,1);
  lcd.print("Test Backlight  ");
  delay (1000);
   
 for (int i=0; i<5; i++){
 lcd.noBacklight();
  delay(200);
  lcd.backlight();
  delay(200);}

  lcd.setCursor(0,1);
  lcd.print("Test noDisplay");
  delay (1000);
  for (int i=0; i<5; i++){
  lcd.noDisplay();
  delay(200);
  lcd.display();
  delay(200);}

  lcd.setCursor(0,1);
  lcd.print("Test UL Cursor ");
  delay (1000);
  for (int i=0; i<5; i++){
  lcd.cursor();
  delay(500);
  lcd.noCursor();
  delay(500);}

  lcd.setCursor(0,1);
  lcd.print("Test BL Cursor ");
  delay (1000);
  for (int i=0; i<5; i++){
  lcd.blink();
  delay(500);
  lcd.noBlink();
  delay(500);}

  lcd.setCursor(0,1);
  lcd.print("Test Text Scroll");
  delay (1000);
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  for (int i=0; i<16; i++){
  lcd.scrollDisplayRight();
  delay(200);}

  for (int i=0; i<16; i++){
  lcd.scrollDisplayLeft();
  delay(200);}

  lcd.setCursor(0,1);
  lcd.print("<- Right to Left");
  delay (1000);
  lcd.clear();
  lcd.rightToLeft();
  lcd.setCursor(15,0);
  lcd.print("Hello, world!");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Left to Right ->");
  delay (1000);
  lcd.leftToRight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");

}

void loop()
{
 // Do nothing here...
}
