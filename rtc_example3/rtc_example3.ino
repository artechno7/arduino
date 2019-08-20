#include <RTClib.h>
#include <Wire.h>

RTC_DS1307 rtc;
char nameDay[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
//byte weekday = 0;

#define LIGHTS1_DIGITAL_PIN 6
#define LIGHTS2_DIGITAL_PIN 7

void setup() {
  // put your setup code here, to run once:
   pinMode(LIGHTS1_DIGITAL_PIN, OUTPUT);
   pinMode(LIGHTS2_DIGITAL_PIN, OUTPUT);
Serial.begin(9600);
Wire.begin();
   rtc.begin();
   if (! rtc.isrunning())
  {
    Serial.println("RTC is NOT running!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();
  //Serial.print(nameDay[weekday-1]);
  Serial.print(nameDay[now.dayOfTheWeek()]);
  Serial.print(",");
  Serial.print(now.year(), DEC);
  Serial.print("/");
  Serial.print(now.month(), DEC);
  Serial.print("/");
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(now.hour(), DEC);
  Serial.print(":");
  Serial.print(now.minute(), DEC);
  Serial.print(":");
  Serial.print(now.second(), DEC);
  Serial.print(")");
  Serial.println();

  Serial.println( );
  delay(1000);
  
       if(now.day(4) & now.hour()== 16 & now.minute() == 30 )
      {
        Serial.println (" lights on");
        digitalWrite (LIGHTS1_DIGITAL_PIN, HIGH);
      }
       else if(now.day()==1 & now.hour()== 15 & now.minute() == 55 )
      {
        Serial.println (" lights off");
        digitalWrite (LIGHTS1_DIGITAL_PIN, LOW);
      }
  }
