/********************************
* name:I2C LCD1602
* function:You should now see your I2C LCD1602 display the flowing characters: "1602 serial" and "- Acoptex.com".
********************************/
//Email:info@acoptex.com
//Website:www.acoptex.com
/********************************/
// libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/**********************************************************/
char array1[]=" 1602 serial               "; //the string to print on the LCD
char array2[]="- Acoptex.com             "; //the string to print on the LCD
int tim = 500; //the value of delay time
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x3F,16,2); // set the LCD address to 0x3F for a 16 chars and 2 line display
/*********************************************************/
void setup()
{
 lcd.init(); //initialize the lcd
 lcd.backlight(); //open the backlight
}
/*********************************************************/
void loop()
{
 lcd.setCursor(15,0); // set the cursor to column 15, line 0
 for (int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++)
 {
   lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
   lcd.print(array1[positionCounter1]); // Print a message to the LCD.
   delay(tim); //wait for 250 microseconds
 }
 lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left  corner.
 lcd.setCursor(15,1); // set the cursor to column 15, line 1
 for (int positionCounter = 0; positionCounter < 26; positionCounter++)
 {
   lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
   lcd.print(array2[positionCounter]); // Print a message to the LCD.
   delay(tim); //wait for 250 microseconds
 }
 lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.
}
