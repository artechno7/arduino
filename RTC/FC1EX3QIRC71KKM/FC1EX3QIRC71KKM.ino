
//NJarpa
// Arduino timer on/off setpoint.
//If you find this code,visit INSTRUCTABLES and type the title above.
//Arduino UNO + RTC 1307 + 16X2 LCD + 4 buttons


#include <LiquidCrystal.h>   //Libraries
#include <RTClib.h>
#include <Wire.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Arduino pins to lcd
//LCD 1602
//RS to 2pin, EN to 3pin, D4 to 4pin, D5 to 5pin, D6 to 6pin, D7 to 7pin
//Contrast=  10K potentiometer: 1 to Vcc, 2(center)to VO, 3 to GND
//Backlight= K to GND(with 1K resistor), A to Vcc
//Vss to GND , Vdd to +5v

RTC_DS1307 RTC;                     // define the Real Time Clock object
//RTC 1307
//SDA to analog 4,  SCL to analog 5

//You need 4 buttons like this,to enter the set points, with 10K resistor to ground (for each one)

//                  To arduino pins(8, 9, 10, 11)
//                        |
//                        |
//              switch    |   
//              _______   |         10K          
//    +5V  0-----0   0----0------/\/\/\/\-------0  to GND

const int DOWN_BUTTONon =9;        //Buttons Pins
const int UP_BUTTONon =8;
const int DOWN_BUTTONoff =11;       
const int UP_BUTTONoff =10;
const int Relay =12;             //Relay pin

//-----Variables for debouncing------//

boolean lastDownONButton = LOW;
boolean currentDownONButton = LOW;
boolean lastUpONButton = LOW;
boolean currentUpONButton = LOW;
boolean lastDownOFFButton = LOW;
boolean currentDownOFFButton = LOW;
boolean lastUpOFFButton = LOW;
boolean currentUpOFFButton = LOW;


int set_on = 12;        //The default "ON" desired time
int set_off= 12;        //The default "OFF" desired time


void setup(){
  pinMode(Relay, OUTPUT);
  
     Wire.begin();
     RTC.begin();
     lcd.begin(16, 2); // Configura lcd numero columnas y filas
     
     lcd.setCursor(0,0);  //Show "TIME" on the LCD
     lcd.print("TIME");
     lcd.setCursor(0,1);
     lcd.print("ON");    //Show "ON" on the lcd
     lcd.setCursor(6,1);
     lcd.print("OFF");  //Show "OFF" on the lcd
}
     
   //----Debouncing function for all buttons----//
boolean debounce(boolean last, int pin)
{
boolean current = digitalRead(pin);
if (last != current)
{
delay(5);
current = digitalRead(pin);
}
return current;
}
     
 

void loop(){
//--------Show current Time On LCD--------//


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

//----Debounce  buttons---//
currentDownONButton = debounce(lastDownONButton, DOWN_BUTTONon);
currentUpONButton = debounce(lastUpONButton, UP_BUTTONon);
currentDownOFFButton = debounce(lastDownOFFButton, DOWN_BUTTONoff);
currentUpOFFButton = debounce(lastUpOFFButton, UP_BUTTONoff);

//-----Turn down the set "ON"-----//
if (lastDownONButton== LOW && currentDownONButton == HIGH)
{
if(set_on>0){    //"ON" Set point  down never lower than 0
set_on--;        
}
else{
  lcd.setCursor(3,1);
  lcd.print("0");
}
}

//----Turn up the set "ON"----//
else if (lastUpONButton== LOW && currentUpONButton == HIGH)
{
  if(set_on<23){   //"ON" Set point up never higher than 23
  set_on++;
}
else{
  lcd.setCursor(3,1);
  lcd.print("23");
}
}

//---Print the set "ON"---//
lcd.setCursor(3,1);
if(set_on < 10){   
  lcd.print("0");
}
lcd.print(set_on);
lastDownONButton = currentDownONButton;
lastUpONButton = currentUpONButton;

//-----Turn down the set "OFF"-----//
if (lastDownOFFButton== LOW && currentDownOFFButton == HIGH)
{
if(set_off>0){    //"OFF" Set point  down never lower than 0
set_off--;
}
else{
  lcd.setCursor(10,1);
  lcd.print("0");
}
}

//----Turn up the set "OFF"----//
else if (lastUpOFFButton== LOW && currentUpOFFButton == HIGH)
{
  if(set_off<23){   //"OFF" Set point up never higher than 23
  set_off++;
}
else{
  lcd.setCursor(10,1);
  lcd.print("23");
}
}

//---Print the set "OFF"---//
lcd.setCursor(10,1);
if(set_off < 10){   
  lcd.print("0");
}
lcd.print(set_off);
lastDownOFFButton = currentDownOFFButton;
lastUpOFFButton = currentUpOFFButton;



//----Relay Function----//
if(set_on == set_off){
   digitalWrite(Relay, LOW);
}

if(set_on < set_off){
  
             if(now.hour() >= set_on && now.hour() < set_off ){             //Start
             digitalWrite(Relay, HIGH);
             }
             else if(now.hour() >= set_off) {
             digitalWrite(Relay, LOW);
             }
             else{
             digitalWrite(Relay, LOW);
             }
}
if (set_on > set_off){

            if(now.hour() >= set_on && now.hour() <= 23){                  //Start
            digitalWrite(Relay, HIGH);  
            }
            else if(now.hour() < set_off){
            digitalWrite(Relay, HIGH);
            }
            else if(now.hour() >= set_off && now.hour() < set_on){
            digitalWrite(Relay, LOW);  
            }
}

}// The End



