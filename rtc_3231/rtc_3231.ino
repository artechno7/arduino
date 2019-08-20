#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "RTClib.h" // library yang kita add tadi
//LiquidCrystal_I2C lcd(0x27, 16, 2); // alamat i2c lcd dan type lcd 16x2
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

RTC_DS3231 rtc;
char hari[7][12] = {"Min", "Sen", "Sel", "Rab", "Kam", "Jum", "Sab"};
 
void setup() {
  lcd.begin(16,2);
  //lcd.backlight();
   
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   
  }  
}
void loop() {
   DateTime now = rtc.now();
   lcd.setCursor(1,0);
   lcd.print(hari[now.dayOfTheWeek()]);
   lcd.print(":");
   printDT(now.day());
   lcd.print("-");
   printDT(now.month());
   lcd.print("-");
   printDT(now.year());
    
   lcd.setCursor(4,1);
   printDT(now.hour());
   lcd.print(":");
   printDT(now.minute());
   lcd.print(":");
   printDT(now.second());
   delay(500);
}
void printDT ( int DT ){
  if ( DT < 10 ){
    lcd.print('0');
    lcd.print(DT);
  }
  else{
    lcd.print(DT);
  }
}
