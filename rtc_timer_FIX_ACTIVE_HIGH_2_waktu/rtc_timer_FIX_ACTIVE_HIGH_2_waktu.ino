#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

int ledPin = 13;         // Set our LED pin

byte startHour = 17;    // Set our start and end times
byte startMinute = 0;  // Don't add leading zero to hour or minute - 7, not 07
byte endHour = 17;      // Use 24h format for the hour, without leading zero
byte endMinute = 1;

//waktu 2
byte startHour2 = 17;    // Set our start and end times
byte startMinute2 = 2;  // Don't add leading zero to hour or minute - 7, not 07
byte endHour2 = 17;      // Use 24h format for the hour, without leading zero
byte endMinute2 = 3;
//


byte validStart = 0;    // Declare and set to 0 our start flag
byte poweredOn = 0;     // Declare and set to 0 our current power flag
byte validEnd = 0;      // Declare and set to 0 our end flag

void setup () {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);   // Set our LED as an output pin
  digitalWrite(ledPin, LOW); // Set the LED to LOW (off)
  
  Wire.begin();              // Start our wire and real time clock
  RTC.begin();
  
  if (! RTC.isrunning()) {                       // Make sure RTC is running
    Serial.println("RTC is NOT running!");
    //RTC.adjust(DateTime(__DATE__, __TIME__));  // Uncomment to set the date and time
  }
}

void loop () {
  
  DateTime now = RTC.now(); // Read in what our current datestamp is from RTC
    
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
  if (now.second() == 0) { // Only process if we have ticked over to new minute
    if (poweredOn == 0) {  // Check if lights currently powered on
      checkStartTime();    // If they are not, check if it's time to turn them on
    }
    if (poweredOn == 1) {
       checkEndTime();
    }
    if (poweredOn == 2) {
      checkStartTime2();
    } 
    else {
        checkEndTime2() ;  // Otherwise, check if it's time to turn them off
    }

  
    if (validStart == 1) { // If our timer is flagged to start, turn the lights on
      turnLightsOn();
      Serial.println("RELAY NYALA");
    }
    if (validEnd == 1) {   // If our time is flagged to end, turn the lights off
      turnLightsOff();
      Serial.println("RELAY MATI");
    }
  }
  
  delay(1000);  
}

byte checkStartTime() {
  DateTime now = RTC.now();  // Read in what our current datestamp is from RTC
  
  if (now.hour() == startHour && now.minute() == startMinute) {
    validStart = 1;  // If our start hour and minute match the current time, set 'on' flags
    poweredOn = 1;
  } else {
    validStart = 0;  // Otherwise we don't need to power up the lights yet
  }
  
  return validStart; // Return the status for powering up
} 

byte checkEndTime() {
  DateTime now = RTC.now();  // Read in what our current datestamp is from RTC
  
  if (now.hour() == endHour && now.minute() == endMinute) {
    validEnd = 1;    // If our end hour and minute match the current time, set the 'off' flags
    poweredOn = 2;
  } else {
    validEnd = 0;    // Otherwise we don't need to power off the lights yet
  }
  
  return validEnd;   // Return the status for powering off
} 

//waktu2
byte checkStartTime2() {
  DateTime now = RTC.now();  // Read in what our current datestamp is from RTC
  
  if (now.hour() == startHour2 && now.minute() == startMinute2) {
    validStart = 1;  // If our start hour and minute match the current time, set 'on' flags
    poweredOn = 3;
  } else {
    validStart = 0;  // Otherwise we don't need to power up the lights yet
  }
  
  return validStart; // Return the status for powering up
} 

byte checkEndTime2() {
  DateTime now = RTC.now();  // Read in what our current datestamp is from RTC
  
  if (now.hour() == endHour2 && now.minute() == endMinute2) {
    validEnd = 1;    // If our end hour and minute match the current time, set the 'off' flags
    poweredOn = 0;
  } else {
    validEnd = 0;    // Otherwise we don't need to power off the lights yet
  }
  
  return validEnd;   // Return the status for powering off
} 
//

void turnLightsOn() {
  digitalWrite(ledPin, HIGH);  // Turn on the LED
}

void turnLightsOff() {
  digitalWrite(ledPin, LOW);   // Turn off the LED
}
