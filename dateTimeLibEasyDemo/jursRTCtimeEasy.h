// RTC and time library for DS1307 and DS3231 realtime clock
// Created by 'jurs' on Easter weekend, 2015
// 06.04.2015: initial version, summertime code only valid for countries in Europe
// 18.04.2015: timer switch logic added 
// 01.05.2015: added different summertime/DST rules for Europe and Australia

#define TIMEZONE 10  // timezone for Germany and most countries in Europe is UTC + 1 hour
#define DST_RULE 1  // 0=European Union, 1=Australia (summertime/DST rules)

#define RTC_I2C_ADDRESS 0x68 // // I2C adress of DS1307 and DS3231 RTC

#include <Arduino.h>
#include <Wire.h>

struct sTime // structure for holding a time including timezone setting
{
  int  iYear;
  byte bMonth;
  byte bDay;
  byte bHour;
  byte bMinute;
  byte bSecond;
  int8_t sTimezone;  // 0=UTC, 1=CET, 2=CEST (Central Europen Summer Time)
};

int wdayS(sTime &time);
int wdayS(sTime &time)
{ // Calculate day of week, Sunday == 0. 
  int adjustment, mm, yy;
  adjustment = (14 - time.bMonth) / 12;
  mm = time.bMonth + 12 * adjustment - 2;
  yy = time.iYear - adjustment;
  return (time.bDay + (13 * mm - 1) / 5 + yy + yy / 4 - yy / 100 + yy / 400) % 7;
}

int wdayM(sTime &time);
int wdayM(sTime &time)
{ // Calculate day of week, Monday == 0. 
  (wdayS(time)+6) % 7;
}


byte daysInMonth(int year, byte month)
{
  if (month == 4 || month == 6 || month == 9 || month == 11)  
    return 30;  
  else if (month == 2)  
  {
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);  
    if (isLeapYear) return 29;
    else return 28;
  }  
  else return 31;
}

boolean assignDateTime(sTime &time, int year, byte month, byte day, byte hour, byte minute, byte second, byte timezone);
boolean assignDateTime(sTime &time, int year, byte month, byte day, byte hour, byte minute, byte second, byte timezone)
{
  if (year<2000 || year>2099 || month<1 || month>12 || day<1 || day>daysInMonth(year,month) 
      || hour>23 || minute>59 || second>59) return false;
  time.iYear=year;
  time.bMonth=month;
  time.bDay=day;
  time.bHour=hour;
  time.bMinute=minute;
  time.bSecond=second;
  time.sTimezone=timezone;
  return true;
}

boolean validDateTime(sTime &time);
boolean validDateTime(sTime &time)
{
  return assignDateTime(time, time.iYear, time.bMonth, time.bDay, time.bHour, time.bMinute, time.bSecond, time.sTimezone);
}


byte decToBcd(byte val) // RTC helper function
// Convert decimal number to binary coded decimal
{
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  // RTC helper function
// Convert binary coded decimal to decimal number
{
  return ( (val/16*10) + (val%16) );
}

boolean RTCinit()
{
  Wire.begin();
  delay(10); // small delay to stabilize I2C bus voltage
  Wire.beginTransmission(RTC_I2C_ADDRESS);
  Wire.write(0);
  return (Wire.endTransmission()==0);
}

boolean summertimeDST(sTime time);
// Daylight Saving Time rules are included by using 'conditional define' of DST_RULE
#if DST_RULE==0   // EUROPEAN UNION

boolean summertimeDST(sTime time)  // EUROPEAN UNION in UTC+1
// European Daylight Savings Time calculation by "jurs" for German Arduino Forum
// time year, month, day, hour and timezone (0=UTC, 1=MEZ, 2=MESZ)
// return value: returns true during Daylight Saving Time, false otherwise
{ 
  if (time.bMonth<3 || time.bMonth>10) return false; // no DST/summertime in Jan, Feb, Nov, Dec
  if (time.bMonth>3 && time.bMonth<10) return true; // always DST/summertime in Apr, May, Jun, Jul, Aug, Sep
  if (time.bMonth==3 && (time.bHour + 24 * time.bDay)>=(1 + time.sTimezone + 24*(31 - (5 * time.iYear /4 + 4) % 7)) || time.bMonth==10 && (time.bHour + 24 * time.bDay)<(1 + time.sTimezone + 24*(31 - (5 * time.iYear /4 + 1) % 7))) 
    return true; 
  else 
    return false;
}

#elif DST_RULE==1  // AUSTRALIA

boolean summertimeDST(sTime time) // AUSTRALIA in AEST=UTC+10
// Australian Daylight Savings Time calculation by "jurs" for German Arduino Forum
// rule: DST from first Sunday in October until first Sunday in April
// return value: returns true during Daylight Saving Time, false otherwise
{ 
  if (time.bMonth<4 || time.bMonth>10) return true; // always DST/summertime in Jan, Feb, Mar, Nov, Dec
  if (time.bMonth>4 && time.bMonth<10) return false; // no DST/summertime in May, Jun, Jul, Aug, Sep
  if (time.bMonth==4 && (time.bHour + 24 * time.bDay)<(-8 + time.sTimezone + 24*(7 - (5 * time.iYear /4 + 4) % 7)) || time.bMonth==10 && (time.bHour + 24 * time.bDay)>=(-8 + time.sTimezone + 24*(7 - (5 * time.iYear /4 + 5) % 7))) 
    return true; 
  else 
    return false;
}

#else
  ERROR: DST RULE NOT AVAILABLE
#endif

void timeAddTimezone(sTime &time);
void timeAddTimezone(sTime &time)
// Add one hour to time and increase timezone
{
  time.bHour++;
  if (time.bHour>23)
  {
    time.bHour=0;
    time.bDay++;
    if (time.bDay>daysInMonth(time.iYear, time.bMonth))
    {
      time.bDay=1;
      time.bMonth++;
      if (time.bMonth>12)
      {
        time.bMonth=1;
        time.iYear++;
      }
    }
  }
  time.sTimezone++;
}

void timeSubTimezone(sTime &time);
void timeSubTimezone(sTime &time)
// Subtract one hour from time and decrease timezone
{
  if (time.bHour>0)
    time.bHour--;
  else  
  {
    time.bHour=23;
    time.bDay--;
    if (time.bDay==0)
    {
      time.bMonth--;
      if (time.bMonth==0)
      {
        time.bMonth=12;
        time.iYear--;
      }
      time.bDay=daysInMonth(time.iYear, time.bMonth);
    }
  }
  time.sTimezone--;
}


void RTCreadZoneTime(sTime &time);
void RTCreadZoneTime(sTime &time)
// read current time from RTC
{
// Reset the register pointer
  Wire.beginTransmission(RTC_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(RTC_I2C_ADDRESS, 7);
  // A few of these need masks because certain bits are control bits
  time.bSecond= bcdToDec(Wire.read() & 0x7f);
  time.bMinute= bcdToDec(Wire.read());
  time.bHour  = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  bcdToDec(Wire.read()); // day of week not used
  time.bDay   = bcdToDec(Wire.read());
  time.bMonth = bcdToDec(Wire.read());
  time.iYear  = bcdToDec(Wire.read())+2000;  
  time.sTimezone=TIMEZONE;
}

void RTCreadLocalTime(sTime &time);
void RTCreadLocalTime(sTime &time)
{
  RTCreadZoneTime(time);
  if (summertimeDST(time)) timeAddTimezone(time);
}

void RTCwrite(sTime time)
// write time to RTC
{
  Wire.beginTransmission(RTC_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(time.bSecond));    // 0 to bit 7 starts the clock
  Wire.write(decToBcd(time.bMinute));
  Wire.write(decToBcd(time.bHour));      // If you want 12 hour am/pm you need to set
                                   // bit 6 (also need to change readDateDs1307)
                                  
  Wire.write(decToBcd(0)); // weekday not used
  Wire.write(decToBcd(time.bDay));
  Wire.write(decToBcd(time.bMonth));
  Wire.write(decToBcd(time.iYear-2000));
  Wire.endTransmission();  
}


char* readSerialCommand()
// reads serial command lines that are finished with a carriage return (CR, ASCII-13)
// non blocking version
// returns true if command is finished with CR (ASCII-13, '\n')
// return false if no input from Serial is available or if command is not yet finished
{
  static char str[26]; // read a command up to 25 chars length + '\0' 
  static byte count=0;
  if (Serial.available())
  {
    while (Serial.available())
    {
      if (count==0) memset(str,0,sizeof(str)); // delete string by writing zeros to it
      char c=Serial.read();
      if (c>=32 && count<sizeof(str)-1) // valid ASCII char
      {
        str[count]=c;
        count++;
      }
      else if (c==13 && count>0) // if carriage return received
      {
        count=0;
        return str;
      }
    }
  }
  return NULL;  
}

boolean handleRtcCommand(char* command)
// handles the time setting commands 'setc' and 'setd'in format 
// "setc YYYY MM DD hh mm ss" or "setd DD.MM.YYYY hh:mm:ss"
// examples for 'setc' and 'setd' commands:
// setc 2016 12 24 09 30
// setd 24.12.2016 9:30
// leading zeros are optional, hours, minutes and seconds are optional (default 00)
{
  sTime time;  
  char delim[]=" .:/-"; // allowed delimiter chars between date/time components
  char* param[6];
  char* temp;
  command=strtok(command,delim); // look for the leading 2 in the year
  for (int i=0; i<6; i++)
  {
    param[i]=strtok(NULL,delim);
  }
  if (command[3]=='d') // must be 'setd' instead of 'setc' command
  { // swap day and year parameters for German format input
    temp=param[0];
    param[0]=param[2];
    param[2]=temp;
  }
  // assume given time to be a time in TIMEZONE
  if (assignDateTime(time, atoi(param[0]), atoi(param[1]), atoi(param[2]), atoi(param[3]), atoi(param[4]), atoi(param[5]), TIMEZONE))
  {
    if (summertimeDST(time))
    {
      time.sTimezone=TIMEZONE+1; // it is summertime, increase timezone
      timeSubTimezone(time); // subtract 1 hour and decrease time to zonetime
    }
    RTCwrite(time); // write time to RTC
    return true;
  }
  else
  return false;
}

// Switch Timer related declarations and function
struct swTime_t{
  int onTime;
  int offTime;
};

boolean isSwitchTime(int thisTime, int onTime, int offTime)
{
  // normal switching during the day: onTime<offTime
  if (onTime<offTime && thisTime>=onTime && thisTime<offTime) return true;
  // else if switching over midnight: onTime>offTime
  if (onTime>offTime && thisTime<onTime && thisTime>=offTime) return true;
  return  false; // off
}

boolean isOnTime(sTime time, swTime_t* switchTime, byte count);
boolean isOnTime(sTime time, swTime_t* switchTime, byte count)
 // parameter 'time': current time in sTime format
 // parameter 'switchTime': array of swTime switching times
 // parameter 'count': number of entries in the swTime array
 // return value 'true' if time is in one of the switching times
{
  // create current time stamp in format 'hours*100+minutes' for comparison
  int thisTime= time.bHour*100+time.bMinute;
  for (int i=0;i<count;i++)
  {
    if (isSwitchTime(thisTime, switchTime[i].onTime, switchTime[i].offTime))
      return true;
  }   
  return false; // if no ON time found after processing all switching times
}

