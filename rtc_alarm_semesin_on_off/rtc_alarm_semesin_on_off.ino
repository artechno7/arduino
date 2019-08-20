#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <EEPROM.h>
 
//pin
byte tombolUp = 3;
byte tombolDn = 4;
byte tombolMinus = 5; //-
byte tombolPlus = 2; //e
byte buzzer = 6;
 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // 0x27 is the I2C bus address for an unmodified backpack
byte detikTerakhir = 60;
 
int alarmJamAddr = 0;
int alarmMenitAddr = 1;
int alarmDetikAddr = 2;
 
byte alarmJam;
byte alarmMenit;
byte alarmDetik;
 
bool alarmStatus = false;
unsigned long millisMulai;
unsigned long millisAlarmMulai;
 
bool buzzStatus;
 
uint16_t jedaBuzzer = 1000; //UNTUK ALARM JEDA MATI HIDUP
uint16_t waktuAlarm = 100000;//Alarm 10 detik
 
byte menu = 0;
byte menuLCDPos = 8;
byte temp;
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Setting alarm menggunakan Arduino dan RTC1307 melalui 4 push button");
  Serial.println("https://www.semesin.com/project");
 
  pinMode(buzzer, OUTPUT);
  pinMode(tombolUp, INPUT_PULLUP);
  pinMode(tombolDn, INPUT_PULLUP);
  pinMode(tombolMinus, INPUT_PULLUP);
  pinMode(tombolPlus, INPUT_PULLUP);
   
  lcd.begin (16,2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
 
  lcd.setCursor (0,0);
  lcd.print("Waktu:    :  :  ");
  lcd.setCursor(0,1);
  lcd.print("Alarm:    :  :  ");
 
  readEEPROMDataWaktu();
 
  lcd.setCursor(8,1);
  if(alarmJam < 10)lcd.print('0');
  lcd.print(alarmJam);
  lcd.setCursor(11,1);
  if(alarmMenit < 10)lcd.print('0');
  lcd.print(alarmMenit);
  lcd.setCursor(14,1);
  if(alarmDetik < 10)lcd.print('0');
  lcd.print(alarmDetik);
}
 
void loop()
{
  tmElements_t tm;
 
  do
  {
    lcd.setCursor(menuLCDPos, 1);
    switch(bacaTombol())
    {
      case '+':
        temp = EEPROM.read(menu - 1);
        if(((temp >= 23) && (menu == 1)) || ((temp >= 59) && (menu > 1)))
          temp = 0;
        else
          temp++;
        EEPROM.write(menu - 1, temp);
        if(temp < 10)lcd.print('0');
        lcd.print(temp);
        break;
      case '-':
        temp = EEPROM.read(menu - 1);
        if((temp == 0) && (menu == 1))
          temp = 23;
        else if((temp == 0) && (menu > 1))
          temp = 59;
        else
          temp--;
        EEPROM.write(menu - 1, temp);
        if(temp < 10)lcd.print('0');
        lcd.print(temp);
        break;
      case 'M':
        menu++;
        if(menu == 1)
        {
          menuLCDPos = 8;
          temp = alarmJam;
          lcd.blink();
        }
        else if(menu == 2)
        {
          menuLCDPos = 11;
        }
        else if(menu == 3)
        {
          menuLCDPos = 14;
        }
        if(menu == 4)
        {
          menu = 0;
          lcd.noBlink();
          readEEPROMDataWaktu();
        }
        break;
      case 'E':
        menu = 0;
        lcd.noBlink();
        readEEPROMDataWaktu();
        break;
    }
  }
  while (menu);
 
  if(alarmStatus)
  {
    if(millisMulai + jedaBuzzer < millis())
    {
      buzzStatus = !buzzStatus;
      digitalWrite(buzzer, buzzStatus); //UNTUK ALARM HIGH DIGANTI buzzstatus
      millisMulai = millis();
    }
    if(millisAlarmMulai + waktuAlarm < millis())
    {
      alarmStatus = false;
      digitalWrite(buzzer, LOW);
    }
  }
 
  if (RTC.read(tm)) {
    if(tm.Second != detikTerakhir)
    {
      lcd.setCursor(8,0);
      if(tm.Hour < 10)lcd.print('0');
      lcd.print(tm.Hour);
      lcd.setCursor(11,0);
      if(tm.Minute < 10)lcd.print('0');
      lcd.print(tm.Minute);
      lcd.setCursor(14,0);
      if(tm.Second < 10)lcd.print('0');
      lcd.print(tm.Second);
 
      if((alarmJam == tm.Hour) && (alarmMenit == tm.Minute) && (alarmDetik == tm.Second))
      {
        alarmStatus = true;
        millisMulai = millis();
        millisAlarmMulai = millisMulai;
      }
 
      detikTerakhir = tm.Second;
    }
  }
}
 
char bacaTombol()
{
  char tombol = ' ';
  if(!digitalRead(tombolUp))
  {
    tombol = '+';
  }
  else if(!digitalRead(tombolDn))
  {
    tombol = '-';
  }
  else if(!digitalRead(tombolMinus))
  {
    tombol = 'M';
  }
  else if(!digitalRead(tombolPlus))
  {
    tombol = 'E';//exit
  }
  while(!digitalRead(tombolUp));
  while(!digitalRead(tombolDn));
  while(!digitalRead(tombolMinus));
  while(!digitalRead(tombolPlus));
  delay(200);
 
  return tombol;
}
 
void readEEPROMDataWaktu()
{
  alarmJam = EEPROM.read(alarmJamAddr);
  alarmMenit = EEPROM.read(alarmMenitAddr);
  alarmDetik = EEPROM.read(alarmDetikAddr);
}
