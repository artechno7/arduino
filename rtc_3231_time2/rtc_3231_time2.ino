#include <DS3231.h>
#include <LiquidCrystal_I2C.h> // includes the LiquidCrystal Library 
DS3231  rtc(SDA, SCL);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup() { 
 rtc.begin(); // Initialize the rtc object
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
}
void loop() { 
 lcd.setCursor(0,0);
 lcd.print("Time:  ");
 lcd.print(rtc.getTimeStr());
 
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(rtc.getDateStr());
 
 delay(1000); 
}
