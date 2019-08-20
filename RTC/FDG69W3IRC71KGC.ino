
//NJarpa
//Simple clock with RTC 1307

#include <LiquidCrystal.h>   //Libraries
#include <RTClib.h>
#include <Wire.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Pines arduino a lcd

//LCD 1602
//2pin to RS, 3pin to EN, D4 to 4pin, D5 to 5pin, D6 to 6pin, D7 to 7pin
//Contrast=  10K potentiometer 1 to Vcc, 2(center)to VO, 3 to GND
//Backlight= K to GND(with 1K resistor), A to Vcc
//Vss to GND , Vdd to +5v
RTC_DS1307 RTC;                     // define the Real Time Clock object

//RTC 1307
//SDA to analog 4,  SCL to analog 5 

void setup(){
     Wire.begin();
     RTC.begin();
     lcd.begin(16, 2); // Configura lcd numero columnas y filas
     
     lcd.setCursor(0,0);  //Show "TIME" on the LCD
     lcd.print("TIME");  
}

void loop(){
//--------Show Actual Time On LCD--------//
DateTime now = RTC.now();        // Clock call
now = RTC.now();
lcd.setCursor(5,0);                 
if(now.hour() < 10)
{
lcd.print("0");
}
lcd.print(now.hour(), DEC); //Print hour
lcd.print(':');
if(now.minute() < 10)
{
lcd.print("0");
}
lcd.print(now.minute(), DEC); //Print min
lcd.print(':');
if(now.second() < 10)
{
lcd.print("0");
}
lcd.print(now.second(), DEC); //Print sec


}


 

