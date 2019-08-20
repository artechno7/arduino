#include <avr/pgmspace.h>
#include <Wire.h>  // include Wire library for I2C devices
#include "jursRTCtimeEasy.h" // include RTC time library

#define LCD_OUTPUT 1 // comment out this line or set 0 if no LCD is used
#define LCDWIDTH 16
#if LCD_OUTPUT==1
  #include "LiquidCrystal.h"
  LiquidCrystal lcd(8,9,4,5,6,7); // LCD pins for 'LCD Keypad Shield'
#endif  

// declare variables used in this program
#define RELAY_ON LOW    // ON==LOW for relay type 'active LOW'
#define RELAY_OFF HIGH  // OFF=HIGH for relay type 'active LOW' 
#define RELAY_PIN 13
byte relayState;

sTime localTime; // holds current time in local time (with regard to DST/summertime)
swTime_t switchTimes[]={ // define ON times
  {500,530},
  {830,900},
  {1200,1230},
  {1530,1600},
  {1900,1930},
  {2230,2300},
};
#define NUMSWITCHTIMES sizeof(switchTimes)/sizeof(switchTimes[0])

void serialTask()
{ // Check Serial input for time setting command
  char* command=readSerialCommand();
  if (command!=NULL) // we have found a command from Serial
  {
    Serial.print(command);Serial.print('\t');
    if (strncmp_P(command,PSTR("setc "),5)==0 || strncmp_P(command,PSTR("setd "),5)==0) // compare for command
    {
      if (handleRtcCommand(command)) Serial.println(F("OK"));
      else Serial.println(F("ERROR: invalid time not set"));
    }
    else Serial.println(F("Unknown command")); // handle other commands here
  }
}

void input()
{
//  RTCreadZoneTime(time); // read zoneTime so that 'time' is a zone time
  RTCreadLocalTime(localTime); // read localTime so that 'time' is a local time
}

void processing()
{
  relayState=isOnTime(localTime,switchTimes, NUMSWITCHTIMES);
}

void output()
// format output and send output to LCD, Serial and OUTPUT pins
// switch relay to on or off accordingly to processed 'relaystate'
{
  char buf[LCDWIDTH+1];
  // format date to 'buf' array
  snprintf_P(buf,sizeof(buf),PSTR("%02d.%02d.%04d  "), localTime.bDay, localTime.bMonth, localTime.iYear);
  if (localTime.bSecond%10==0) Serial.print(buf); 
#if LCD_OUTPUT==1 // if output on LCD is enabled
  lcd.setCursor(0,0);
  lcd.print(buf);
#endif  

  // timer switch for relay and finally format time and relay status to text  
  char * relayText;
  if (relayState) 
  {
    digitalWrite(RELAY_PIN, RELAY_ON);
    relayText="ON "; 
  }  
  else 
  {
    digitalWrite(RELAY_PIN, RELAY_OFF);
    relayText="OFF";
  }
  snprintf_P(buf,sizeof(buf),PSTR("%02d:%02d:%02d   %s"), localTime.bHour, localTime.bMinute, localTime.bSecond,relayText);
  if (localTime.sTimezone==TIMEZONE+1) buf[8]='*'; // set summertime flag in buf
  if (localTime.bSecond%10==0)
  {
    Serial.println(buf); 
  }
#if LCD_OUTPUT==1 // if output on LCD is enabled
  if (localTime.bSecond%2==1) // if number of seconds is odd, clear ':' in time formatting
  {
    buf[2]=' ';
    buf[5]=' ';
  }
  lcd.setCursor(0,1);
  lcd.print(buf);
#endif  
}


void usage()
{ // show some information about program usage
  Serial.println(F("\nRTC date and time library demo by 'jurs' for German Arduino forum\n"));
  Serial.println(F("Usage for setting RTC date/time from Serial monitor in format"));
  Serial.println(F("setc YYYY MM DD hh mm ss"));
  Serial.println(F("examples:"));
  Serial.println(F("setc 2015 4 6 13 30         (13:30h on 6th of April, 2015)"));
  Serial.println(F("setc 2016 12 24 9 30        (09:30h on 24th of December, 2016)"));
  Serial.println(F("\nOr you can use German date formatting with the 'setd' command:"));
  Serial.println(F("setd 6.4.2015 13:30         (6. April 2015 um 13:30 Uhr)"));
  Serial.println(F("setd 24.12.2016 9:30:12     (24. Dezember 2016 um 9:30:12 Uhr)"));
  Serial.println(F("Time setting is in local time during summertime!\n\n"));
}

void setup() 
{
  digitalWrite(RELAY_PIN, RELAY_OFF); // pull relay pin to off first
  pinMode(RELAY_PIN, OUTPUT);  // then enable relay pin as OUTPUT
  Serial.begin(9600); // enable Serial
#if LCD_OUTPUT==1
  lcd.begin(LCDWIDTH,2);  // enable LCD
#endif  
  usage();
  if (RTCinit()) Serial.println(F("RTC OK"));
  else Serial.println(F("RTC/I2C ERROR"));
}

void loop() 
{
  #define UPDATEINTERVAL 1000
  static unsigned long lastUpdateTime;
  serialTask();
  if (millis()-lastUpdateTime>=UPDATEINTERVAL)
  {
    lastUpdateTime+=UPDATEINTERVAL;
    input();
    processing();
    output();
  }
}
