

//<strong>www.nyebarilmu.com</strong>
//<strong>2019</strong>
//<strong>Digital Clock Module RTC DS1307 with setting push button</strong>

#include <JC_Button.h> 
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include "RTClib.h"
#include <EEPROM.h>

char daysOfTheWeek[7][12] = {"Min", "Sen", "Sel", "Rab", "Kam", "Jum", "Sab"};

RTC_DS1307 rtc; 
LiquidCrystal_PCF8574 lcd(0x27);

int jam, menit, tanggal, bulan, tahun;
int jam1, menit1, tanggal1, bulan1, tahun1;

int state_alrm=1;
int jam_alrm=00, menit_alrm=00;

const byte
BUTTON_PIN(2), relay_alrm(13),
BUTTON_PIN2(3),
BUTTON_PIN3(4),
BUTTON_PIN4(5);  
             
Button 
myBtn(BUTTON_PIN),
myBtn2(BUTTON_PIN2),
myBtn3(BUTTON_PIN3),
myBtn4(BUTTON_PIN4);    

void setup()
{
  lcd.begin(16, 2); // 16 baris, 2 kolom
lcd.setBacklight(255); //menyalakan lampu latar
 
lcd.setCursor(00,00);
lcd.print("Excellent");
lcd.setCursor(00,1);
lcd.print("DIGITAL CLOCK");
delay(2000);
lcd.clear();

    myBtn.begin();  
    myBtn2.begin();
    myBtn3.begin();
    myBtn4.begin();         
    pinMode(relay_alrm, OUTPUT);
    
  digitalWrite(relay_alrm, LOW);
}

void loop()
{
    static bool ledState;       
    myBtn.read();
    myBtn2.read();
    myBtn3.read();
    myBtn4.read();

DateTime now = rtc.now();
    lcd.setCursor(00,00);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(",");
    lcd.setCursor(4,00);
    if (now.day()<=9){lcd.print("0");}
    lcd.print(now.day(), DEC);
    lcd.print('-');
    if (now.month()<=9){lcd.print("0");}
    lcd.print(now.month(), DEC);
    lcd.print('-');
    lcd.print(now.year(), DEC);

    lcd.setCursor(00,1);
    if (now.hour()<=9){lcd.print("0");}
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    if (now.minute()<=9){lcd.print("0");}
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    if (now.second()<=9){lcd.print("0");}
    lcd.print(now.second(), DEC);   

    jam = now.hour(),DEC;
    menit = now.minute(),DEC;

    state_alrm = EEPROM.read(00);
    jam_alrm = EEPROM.read(1);
    menit_alrm = EEPROM.read(2);
    
  if(state_alrm==1) {lcd.setCursor(10,1);lcd.print("#");}
  if(state_alrm==2) {lcd.setCursor(10,1);lcd.print("*");}

  lcd.setCursor(11,1);lcd.print(jam_alrm);
  lcd.setCursor(13,1);lcd.print(":");
  lcd.setCursor(14,1);lcd.print(menit_alrm);
  if(state_alrm == 2 && jam_alrm == jam && menit_alrm==menit) {digitalWrite(relay_alrm, HIGH);}
  if(state_alrm == 2 && menit_alrm+3) {digitalWrite(relay_alrm, LOW);}
  if (myBtn4.wasReleased())  {digitalWrite(relay_alrm, LOW);}
  
    if (myBtn.wasReleased())  {Settings();}
}

void Settings(){
    lcd.clear();
     int a = 1;
    while(1){
      myBtn.read();
      myBtn2.read();
      myBtn3.read();
      myBtn4.read();
      lcd.setCursor(00,00);lcd.print("Setting Menu");
      lcd.setCursor(1,1);lcd.print("Date");
      lcd.setCursor(11,1);lcd.print("Alrm");
      
      if (myBtn2.wasReleased())  {a++; if(a==3) a=1;}
      if (myBtn3.wasReleased())  {a--; if(a==-1) a=2;}
      switch(a){
      case 1:
      lcd.setCursor(00,1);lcd.print(">");
      lcd.setCursor(10,1);lcd.print(" ");
      if (myBtn.wasReleased())  {Set_date();}
      break;
      case 2:
      lcd.setCursor(00,1);lcd.print(" ");
      lcd.setCursor(10,1);lcd.print(">");
     if (myBtn.wasReleased())  {Set_alrm();}
      break;
    }
    if (myBtn4.wasReleased()) { lcd.clear();break;}
}
}

void Set_date(){
  lcd.clear();
    int b = 1;
    DateTime now = rtc.now();
    jam = now.hour(),DEC;
    menit = now.minute(),DEC;
    tanggal = now.day(),DEC;
    bulan = now.month(),DEC;
    tahun = now.year(),DEC;

    while(1){
      myBtn.read();
      myBtn2.read();
      myBtn3.read();
      myBtn4.read();
     if (myBtn.wasReleased())  {b++; if(b==7) b=1;}
     
       lcd.setCursor(00,00);lcd.print(jam,DEC);
       lcd.setCursor(2,00);lcd.print(":");
       lcd.setCursor(3,00);lcd.print(menit,DEC);
       lcd.setCursor(00,1);lcd.print(tanggal,DEC);
       lcd.setCursor(2,1);lcd.print("-");
       lcd.setCursor(3,1);lcd.print(bulan,DEC);
       lcd.setCursor(5,1);lcd.print("-");
       lcd.setCursor(6,1);lcd.print(tahun,DEC);
       lcd.setCursor(11,1);lcd.print("SAVE");
      
      switch(b){
      case 1:
      lcd.setCursor(00,00);lcd.print(jam,DEC);
      lcd.setCursor(00,00);lcd.print("  ");
      lcd.setCursor(2,00);lcd.print(":");
      if (myBtn2.wasReleased())  {jam++; if(jam==24) jam=0;}
      if (myBtn3.wasReleased())  {jam--; if(jam==-1) jam=23;}
      break;
      case 2:
      lcd.setCursor(3,00);lcd.print(menit,DEC);
      lcd.setCursor(3,00);lcd.print("  ");
      if (myBtn2.wasReleased())  {menit++; if(menit==60) menit=0;}
      if (myBtn3.wasReleased())  {menit--; if(menit==-1) menit=59;}
      break;
      case 3:
      lcd.setCursor(00,1);lcd.print(tanggal,DEC);
      lcd.setCursor(00,1);lcd.print("  ");
      lcd.setCursor(2,1);lcd.print("-");
      if (myBtn2.wasReleased())  {tanggal++; if(tanggal==32) tanggal=1;}
      if (myBtn3.wasReleased())  {tanggal--; if(tanggal==0) tanggal=31;}
      break;
      case 4:
      lcd.setCursor(3,1);lcd.print(bulan,DEC);
      lcd.setCursor(3,1);lcd.print("  ");
      lcd.setCursor(5,1);lcd.print("-");
      if (myBtn2.wasReleased())  {bulan++; if(bulan==13) bulan=1;}
      if (myBtn3.wasReleased())  {bulan--; if(bulan==0) bulan=12;}
      break;
      case 5:
      lcd.setCursor(6,1);lcd.print(tahun,DEC);
      lcd.setCursor(6,1);lcd.print("    ");
      if (myBtn2.wasReleased())  {tahun++; if(tahun==2100) tahun=2000;}
      if (myBtn3.wasReleased())  {tahun--; if(tahun==1999) tahun=2099;}
      break;
      case 6:
      lcd.setCursor(11,1);lcd.print("SAVE");
      lcd.setCursor(11,1);lcd.print("    ");
      if (myBtn2.wasReleased())  { 
        jam1=jam; menit1=menit; tanggal1=tanggal; bulan1=bulan; tahun1=tahun;
        rtc.adjust(DateTime(tahun1,bulan1,tanggal1,jam1,menit1,0));
        lcd.setCursor(00,00);lcd.print("Data tersimpan..");
        delay(1000);lcd.clear();}
      break;
}
if (myBtn4.wasReleased()) { lcd.clear();break;}
    }
}

void Set_alrm(){
  lcd.clear();
  int c = 1;
  
  state_alrm = EEPROM.read(00);
  jam_alrm = EEPROM.read(1);
  menit_alrm = EEPROM.read(2);

 while(1){
  myBtn.read();
  myBtn2.read();
  myBtn3.read();
  myBtn4.read();
     
  lcd.setCursor(00,00);lcd.print("Status:");
  if(state_alrm==1) {lcd.setCursor(7,00);lcd.print("OFF");}
  if(state_alrm==2) {lcd.setCursor(7,00);lcd.print("ON ");}
  lcd.setCursor(00,1);lcd.print("Waktu:");
  lcd.setCursor(6,1);lcd.print(jam_alrm);
  lcd.setCursor(8,1);lcd.print(":");
  lcd.setCursor(9,1);lcd.print(menit_alrm);
  lcd.setCursor(11,1);lcd.print("SAVE");
 if (myBtn.wasReleased())  {c++; if(c==5) c=1;}
      switch(c){
      case 1:
      if(state_alrm==1) {lcd.setCursor(7,00);lcd.print("OFF");}
      if(state_alrm==2) {lcd.setCursor(7,00);lcd.print("ON ");}
      lcd.setCursor(7,00);lcd.print("   ");
      if (myBtn2.wasReleased())  {state_alrm++; if(state_alrm==3) state_alrm=1;}
      if (myBtn3.wasReleased())  {{state_alrm--; if(state_alrm==0) state_alrm=2;}
      break;
      case 2:
      lcd.setCursor(6,1);lcd.print(jam_alrm);
      lcd.setCursor(6,1);lcd.print("  ");
      if (myBtn2.wasReleased())  {jam_alrm++; if(jam_alrm==24) jam_alrm=0;}
      if (myBtn3.wasReleased())  {jam_alrm--; if(jam_alrm==-1) jam_alrm=23;}
      break;
      case 3:
      lcd.setCursor(9,1);lcd.print(menit_alrm);
      lcd.setCursor(9,1);lcd.print("  ");
      if (myBtn2.wasReleased())  {menit_alrm++; if(menit_alrm==60) menit_alrm=0;}
      if (myBtn3.wasReleased())  {menit_alrm--; if(menit_alrm==-1) menit_alrm=59;}
      break;
      case 4:
      lcd.setCursor(11,1);lcd.print("SAVE");
      lcd.setCursor(11,1);lcd.print("    ");
      if (myBtn2.wasReleased())  { 
        EEPROM.write(00,state_alrm);
        EEPROM.write(1,jam_alrm);
        EEPROM.write(2,menit_alrm);
        lcd.setCursor(00,00);lcd.print("Data tersimpan..");
        delay(1000);lcd.clear();}
      break;
}
    }
if (myBtn4.wasReleased()) { lcd.clear();break;}
}
}
