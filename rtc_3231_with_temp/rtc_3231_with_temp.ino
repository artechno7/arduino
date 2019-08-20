#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
DS3231  rtc(SDA, SCL);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup() {
 rtc.begin();
 lcd.begin(16,2);
  //rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(1, 15, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(6, 6, 2017);   // Day, Month, Year
}
void loop() {
 lcd.setCursor(0,0);
 lcd.print("Real Time Clock  ");
 lcd.setCursor(0,1);
 lcd.print("Time: ");
 lcd.print(rtc.getTimeStr());
 delay(3000);
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(rtc.getDateStr());
 delay(3000);
 lcd.setCursor(0,1);
 lcd.print("Day: ");
 lcd.print(rtc.getDOWStr());
 lcd.print("           ");
 delay(3000);
 lcd.setCursor(0,1);
 lcd.print("Temp: ");
 lcd.print(rtc.getTemp());
 lcd.print(" C");
 lcd.print("          ");
 delay(3000);
}
