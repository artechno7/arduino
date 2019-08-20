#include <Wire.h>
#include<EEPROM.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
RTC_DS1307 RTC;
int tmp,Inc,hor,mIn,add=11;
int set=4;  
int cge=3;   
int mod=2;
int off=0;
#define buz 6
int Hor,Min,Sec;
///////////////////////////////////////Fungsi untuk menyesuaikan waktu//////////////////////////////////
void time()                             
{
    int tmp=1,mins=0,hors=0,secs=0;
    while(tmp==1)
    {
     off=0;
     if(digitalRead(cge)==0)
     {
      Hor++;
      if(Hor==24)
      {
       Hor=0;
      }
     }
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Set Waktu Alarm  ");

    lcd.setCursor(0,1);
    if(Hor<=9)
    lcd.print("0");
    lcd.print(Hor);
    lcd.print(":");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("  ");
    lcd.print(":");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    delay(200);
    if(digitalRead(set)==0)
    {
      hor=Hor;
      EEPROM.write(add++,hor);
     tmp=2;
     while(digitalRead(set)==0);
    }
    }
    
    while(tmp==2)
    {
     if(digitalRead(cge)==0)
     {
      Min++;
      if(Min==60)
      {Min=0;}
     }
    lcd.setCursor(0,1);
    lcd.print(Hor);
    lcd.print(":");
     if(Min<=9)
    lcd.print("0");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    lcd.print("  ");
    delay(200);
     lcd.setCursor(0,1);
    lcd.print(Hor);
    lcd.print(":");
    lcd.print("  ");
    lcd.print(":");
    lcd.print(Sec);
    lcd.print("  ");
    delay(200);
      if(digitalRead(set)==0)
      {
       mIn=Min;
       EEPROM.write(add++, mIn);
       tmp=0;
       while(digitalRead(set)==0);
      }
    }
    off=1;
    delay(10);
}
///////////////////////////////////////////fungsi untuk membunyikan  buzzer//////////////////////////////////
void Buz()
{
  if(digitalRead(set)==0)
  off=0;
  if(off==1)
  {
   digitalWrite(buz,HIGH);
   delay(500);
  
   digitalWrite(buz, LOW);
   delay(500);
  }
}
//////////////////////////////////////////fungsi untuk membandingkan alarm dengan waktu RTC//////////////////
void TimeCheck()
{
  int tem[17];
  for(int i=11;i<17;i++)
  {
    tem[i]=EEPROM.read(i);
  }
  if(Hor == tem[11] && Min == tem[12] && off==1)
  {
   add=11;
   Buz();
   Buz();
   lcd.clear();
   lcd.print("alarm...........");
   lcd.setCursor(0,1);
   lcd.print("...........alarm");
   Buz();
   Buz();
    }
}
////////////////////////////////////////////////////////////setup///////////////////////////
void setup()
{
 Wire.begin();
 RTC.begin();
 lcd.begin(16,2);
 pinMode(cge, INPUT);
 pinMode(set, INPUT);
 pinMode(mod, INPUT);
 pinMode(buz, OUTPUT);
 digitalWrite(set, HIGH);
 digitalWrite(mod, HIGH);
 digitalWrite(cge, HIGH);

   lcd.setCursor(0,0);
   lcd.print("Imam Sholahudin");
   lcd.setCursor(0,1);
   lcd.print("  Alarm Clock  ");
   delay(2000);
   lcd.clear();
 if(!RTC.isrunning())
 {
 RTC.adjust(DateTime(__DATE__,__TIME__));
 }
}
////////////////////////////////////////////////////////////loop/////////////////////////////////////
void loop()
{
   DateTime now = RTC.now();
   if(digitalRead(mod) == 0)      
   {
    current();
    time();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Alarm On");
    delay(2000);
   }
 //lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Time:");
 lcd.setCursor(6,0);
 Hor=now.hour(),DEC;
 if(Hor<=9)
 {
  lcd.print("0");
  lcd.print(Hor=now.hour(),DEC);
 }
 else
 lcd.print(Hor=now.hour(),DEC);
 lcd.print(":");
 Min=now.minute(),DEC;
 if(Min<=9)
 {
 lcd.print("0");
 lcd.print(Min=now.minute(),DEC);
 }
 else
 lcd.print(Min=now.minute(),DEC);

 lcd.print(":");
 Sec=now.second(),DEC;
 if(Sec<=9)
 {
  lcd.print("0");
  lcd.print(Sec=now.second(),DEC);
 }
 else
 lcd.print(Sec=now.second(),DEC);
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(now.day(),DEC);
 lcd.print("/");
 lcd.print(now.month(),DEC);
 lcd.print("/");
 lcd.print(now.year(),DEC);
 TimeCheck();
 delay(200);
}
///////////////////////////////////////////////////////fungsi untuk mengambil waktu RTC //////////////////////////////
void current()
{
  lcd.setCursor(0,1);
  lcd.print(Hor);
  lcd.print(":");
  lcd.print(Min);
  lcd.print(":");
  lcd.print(Sec);
}
