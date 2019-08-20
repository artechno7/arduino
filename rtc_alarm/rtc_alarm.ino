/*
* TimeAlarmExample.pde
*
* This example calls alarm functions at 8:30 am and at 5:45 pm (17:45)
* and simulates turning lights on at night and off in the morning
* A weekly timer is set for Saturdays at 8:30:30
*
* A timer is called every 15 seconds
* Another timer is called once only after 10 seconds
*
* At startup the time is set to Jan 1 2011  8:29 am
*/

#include <Time.h>
#include <TimeAlarms.h>
#include <Wire.h>
#define DS1307_I2C_ADDRESS 0x68

int ledPin =  7;

// for RTC work
byte RTCsecond, RTCminute, RTChour, RTCdayOfWeek, RTCdayOfMonth, RTCmonth, RTCyear;



void setup()
{
  pinMode(ledPin, OUTPUT); // show the status
  Serial.begin(9600); // for debugging
  Serial.flush(); // need to flush serial buffer, otherwise first read from reset/power on may not be correct
  Wire.begin(); // initialise i2c bus for DS1307 
  
  clkSync();
  
// create the alarms 
  Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  Alarm.alarmRepeat(15,16,0,EveningAlarm);  // 5:45pm every day 
  Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 


  Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds    
  Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 
}

void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

// functions to be called when an alarm triggers:
void MorningAlarm(){
  Serial.println("Alarm: - turn lights off");    
}

void EveningAlarm(){
  Serial.println("Alarm: - turn lights on");           
}

void WeeklyAlarm(){
  Serial.println("Alarm: - its Monday Morning");      
}

void ExplicitAlarm(){
  Serial.println("Alarm: - this triggers only at the given date and time");       
}

void Repeats(){
  Serial.println("15 second timer");         
}

void OnceOnly(){
  Serial.println("This timer only triggers once");  
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}




void setDateDs1307(byte RTCsecond,        // 0-59
byte RTCminute,        // 0-59
byte RTChour,          // 1-23
byte RTCdayOfWeek,     // 1-7
byte RTCdayOfMonth,    // 1-28/29/30/31
byte RTCmonth,         // 1-12
byte RTCyear)          // 0-99
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(RTCsecond));    // 0 to bit 7 starts the clock
  Wire.write(decToBcd(RTCminute));
  Wire.write(decToBcd(RTChour));      // If you want 12 hour am/pm you need to set
  // bit 6 (also need to change readDateDs1307)
  Wire.write(decToBcd(RTCdayOfWeek));
  Wire.write(decToBcd(RTCdayOfMonth));
  Wire.write(decToBcd(RTCmonth));
  Wire.write(decToBcd(RTCyear));
  Wire.endTransmission();
}

// Gets the date and time from the ds1307
void getDateDs1307(byte *RTCsecond,
byte *RTCminute,
byte *RTChour,
byte *RTCdayOfWeek,
byte *RTCdayOfMonth,
byte *RTCmonth,
byte *RTCyear)
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  // A few of these need masks because certain bits are control bits
  *RTCsecond     = bcdToDec(Wire.read() & 0x7f);
  *RTCminute     = bcdToDec(Wire.read());
  *RTChour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  *RTCdayOfWeek  = bcdToDec(Wire.read());
  *RTCdayOfMonth = bcdToDec(Wire.read());
  *RTCmonth      = bcdToDec(Wire.read());
  *RTCyear       = bcdToDec(Wire.read());
}

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}

void clkSync()
{
  
    getDateDs1307(&RTCsecond, &RTCminute, &RTChour, &RTCdayOfWeek, &RTCdayOfMonth, &RTCmonth, &RTCyear);
    setTime(RTChour,RTCminute,RTCsecond,RTCmonth,RTCdayOfMonth,RTCyear); // set time to Saturday 8:29:00am Jan 1 2011


}
