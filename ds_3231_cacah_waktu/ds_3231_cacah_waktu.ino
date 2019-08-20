#include <DS3231.h>
#include <Wire.h>  // i2C Conection Library

// Init DS3231
DS3231  rtc(SDA, SCL);
// Init a Time-data structure
Time  t;
uint32_t targetTime = 0;

uint8_t hh = 0, mm = 0, ss = 0, dd = 0, bb = 0; //variable Unsignet int 0-255
int yy = 0; //variable integer
String Day = "  "; //variable string

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:
t = rtc.getTime();  // gate all data time & date from RTC
Day = rtc.getDOWStr(); //get name of day

hh = t.hour,DEC; //pengambilan data jam
mm = t.min,DEC; //pengambilan data menit
ss = t.sec,DEC; //pengambilan data detik
dd = t.date,DEC; //pengambilan data hari
bb = t.mon,DEC; //pengambilan data bulan (dalam desimal)
yy = t.year,DEC; //pengambilan data tahun

//Buka Serial Monitor Arduino untuk melihat hasilnya
Serial.print (Day);
Serial.print (F(" Time = "));
Serial.print (hh); Serial.print (F(" : "));
Serial.print (mm); Serial.print (F(" : "));
Serial.print (ss); Serial.print (F("  Date = "));
Serial.print (dd); Serial.print (F(" . "));
Serial.print (bb); Serial.print (F(" . "));
Serial.println (yy);
delay (1000); 
}
