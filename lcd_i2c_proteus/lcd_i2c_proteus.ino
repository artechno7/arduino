#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //0x20 adalah alamat i2c PCF8574 di proteus 
 
void setup()
{
 lcd.begin(16, 2);                     
 lcd.backlight();
 lcd.print("Achmad Fatoni");
}
void loop()
{
}
