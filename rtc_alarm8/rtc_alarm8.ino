#include "Wire.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define DS3231_I2C_ADDRESS 0x68
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

const int buttonPin1 = A0;     // the number of the pushbutton pin
const int buttonPin2 = A1;     // the number of the pushbutton pin
const int buttonPin3 = A2;     // the number of the pushbutton pin
const int buttonPin4 = 2;     // the number of the pushbutton pin
const int buttonPin5 = 3;     // the number of the pushbutton pin

int buttonState1 = 0;        
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;

int a = 0;
int mmz = 0;
int detz = 0;
int menz = 0;
int jamz = 0;

int stm = 0;
int stj = 0;
int savestj = 0;
int savestm = 0;

void setup()
{
  lcd.begin(16, 2); 
  lcd.clear(); 
  lcd.noCursor();
  Wire.begin();
  pinMode(6, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  
  
  //Serial.begin(9600);
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  // setDS3231time(0,12,02,2,5,1,16);
}
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}


void displayTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  lcd.setCursor(0, 0);
  lcd.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  lcd.print(":");
  if (minute<10)
  {
    lcd.print("0");
  }
  lcd.print(minute, DEC);  
  lcd.print(":");
  if (second<10)
  {
    lcd.print("0");
  }
  lcd.print(second, DEC);
  
  lcd.setCursor(0, 1);
  lcd.print(dayOfMonth, DEC);
  lcd.print("/");
  lcd.print(month, DEC);
  lcd.print("/");
  lcd.print(year, DEC);

  if ((hour == savestj) && (minute == savestm)) {
  digitalWrite(8, HIGH);
  } 

}

void loop()
{
  digitalWrite(8, LOW);

  mmz = 0;
  detz = 0;
  menz = 0;
  jamz = 0;
  
  stj = savestj;
  stm = savestm; 
     
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);

  if ( buttonState2 == LOW ){
  delay(200);
  a = a + 1;
   
  if ( a > 2 ) {
  a = 0;
  } else if (a < 0) {
  a = 2;
  }
  
  }
  
  else if ( buttonState3 == LOW ) {
  delay(200);
  a = a - 1;
   
  if ( a > 2 ) {
  a = 0;
  } else if (a < 0) {
  a = 2;
  }
  
  }

  
  if ( a == 0 ) {
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("PILIH MENU");
  lcd.setCursor(0, 1);
  lcd.print(" JAM ");
  delay(500);
        
  }

  else if ( a == 1 ) {
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("PILIH MENU");
  lcd.setCursor(0, 1);
  lcd.print(" SET ALARM ");
  delay(500);
  }

  else if ( a == 2 ) {
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("PILIH MENU");
  lcd.setCursor(0, 1);
  lcd.print(" STOPWATCH ");
  delay(500);
  }
   
  if (( buttonState5 == LOW ) && ( a == 0 )) {
  lcd.clear();
  
  while ( buttonState1 == HIGH )  
  {
    delay(200);
    buttonState1 = digitalRead(buttonPin1); 
    displayTime();
       
  }
      
  }
  
  
  if (( buttonState5 == LOW ) && ( a == 1 )) {
  lcd.clear();
  
  while ( buttonState1 == HIGH )  
  {
    
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);

  lcd.setCursor(0, 0);
  lcd.print("Set Jam : ");
  lcd.print(stj);
  lcd.setCursor(0, 1);
  lcd.print("Set Menit : ");
  lcd.print(stm);  
  delay(200);
  
  if ( buttonState3 == LOW ){
  stj = 0;
  stm = 0;
  lcd.clear();  
  }
  else if ( buttonState4 == LOW ){
  stj = stj + 1;
  lcd.clear();  
  }
  else if ( buttonState5 == LOW ){
  stm = stm + 1;
  lcd.clear();  
  }
  else if ( buttonState1 == LOW ){
  savestm = stm;
  savestj = stj;
  }

   }      
  }
  
  
  if (( buttonState5 == LOW ) && ( a == 2 )) {
  lcd.clear();
  
  while ( buttonState1 == HIGH )  
  {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
      
  mmz = mmz + 1;
  delay(10);
  
  if (mmz == 100) {
  detz = detz + 1;
  mmz = 0;
  }
  if (detz == 60) {
  menz = menz + 1;
  detz = 0;
  }  
  if (menz == 60) {
  jamz = jamz + 1;
  menz = 0;
  }  
    
  lcd.setCursor(0, 0);
  lcd.print(jamz);
  lcd.print(":");
  lcd.print(menz);
  lcd.print(":");
  lcd.print(detz);
  lcd.print(":");
  lcd.print(mmz);
  
  if ( buttonState4 == LOW ){
  delay(200);
  while (buttonState3 == HIGH)
  {  
  lcd.setCursor(0, 0);
  lcd.print(jamz);
  lcd.print(":");
  lcd.print(menz);
  lcd.print(":");
  lcd.print(detz);
  lcd.print(":");
  lcd.print(mmz);
  delay(1000);
  buttonState3 = digitalRead(buttonPin3);
  buttonState1 = digitalRead(buttonPin1);

  
  }
    
  }
       
  }
        
  }  
}
