//                .-~~~~~~~~~-._       _.-~~~~~~~~~-.
//            __.' Create by.   ~.   .~      www.    `.__
//          .'//    DANI RJC      \./   belajarduino   \\`.
//        .'//       2016          |        .com         \\`.
//      .'// .-~"""""""~~~~-._     |     _,-~~~~"""""""~-. \\`.
//    .'//.-"                 `-.  |  .-'                 "-.\\`.
//  .'//______.============-..   \ | /   ..-============.______\\`.
//.'______________________________\|/______________________________`.

#include <DS3231.h> //Memanggil RTC3231 Library
#include <Wire.h>  // i2C Conection Library
#include <LiquidCrystal_I2C.h>  //Memanggil i2C LCD Library
#include <Button.h> //Memanggil library Push Button
#include <EEPROM.h>

#define ON 0 //Ganti 0 jadi 1 saat pakai High Active Trigger
#define OFF 1 //Ganti 1 jadi 0 saat pakai High Active Trigger

//Setup Tombol Setting
#define DN_PIN A0 //Decrease Button
#define UP_PIN A1 //Increase Button
#define SET_PIN A2  //Setup Clock Button
#define ALR_PIN A3  //Setup Timer Button
#define PULLUP true //Mengaktifkan internal Pull Up
#define INVERT true 
#define DEBOUNCE_MS 20     
#define REPEAT_FIRST 500 
#define REPEAT_INCR 100 

//Declare push buttons
Button btnUP(UP_PIN, PULLUP, INVERT, DEBOUNCE_MS);    
Button btnDN(DN_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btnSET(SET_PIN, PULLUP, INVERT, DEBOUNCE_MS);
Button btnALR(ALR_PIN, PULLUP, INVERT, DEBOUNCE_MS);
enum {WAIT, INCR, DECR};             
uint8_t STATE;                       
int count;                           
int lastCount = -1;                   
unsigned long rpt = REPEAT_FIRST;  

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//custom degrees char
uint8_t dgrsChar[8] = {0x4,0xa,0x4,0x0,0x0,0x0,0x0,0x0}; 

// Init DS3231
DS3231  rtc(SDA, SCL);

// Init a Time-data structure
Time  t; //pencacah string time()

uint8_t hh = 0, mm = 0, ss = 0, dd = 0, bb = 0;
int yy = 0;
String Day = "  ";
uint8_t StartHH  = 21, StartMM  = 43, FinishHH  = 21, FinishMM  = 44, setMode = 0, setAlarm = 0, alarmMode=0;
uint8_t StartHH2 = 21, StartMM2 = 44, FinishHH2 = 21, FinishMM2 = 45;
uint8_t StartHH3 = 21, StartMM3 = 45, FinishHH3 = 21, FinishMM3 = 46;
uint8_t StartHH4 = 21, StartMM4 = 46, FinishHH4 = 21, FinishMM4 = 47;
uint8_t StartHH5 = 21, StartMM5 = 47, FinishHH5 = 21, FinishMM5 = 48;
uint8_t StartHH6 = 21, StartMM6 = 48, FinishHH6 = 21, FinishMM6 = 49;
uint8_t StartHH7 = 21, StartMM7 = 49, FinishHH7 = 21, FinishMM7 = 50;
uint8_t StartHH8 = 21, StartMM8 = 50, FinishHH8 = 21, FinishMM8 = 51;

//Eeprom Store Variable
uint8_t HH,HH2,HH3,HH4,HH5,HH6,HH7,HH8;
uint8_t MM,MM2,MM3,MM4,MM5,MM6,MM7,MM8;

void setup()
{
  // Setup Serial connection
  //Serial.begin(115200);
 pinMode(2,OUTPUT);digitalWrite (2,OFF); 
 pinMode(3,OUTPUT);digitalWrite (3,OFF); 
 pinMode(4,OUTPUT);digitalWrite (4,OFF); 
 pinMode(5,OUTPUT);digitalWrite (5,OFF);
 pinMode(6,OUTPUT);digitalWrite (6,OFF); 
 pinMode(7,OUTPUT);digitalWrite (7,OFF);
 pinMode(8,OUTPUT);digitalWrite (8,OFF);
 pinMode(9,OUTPUT);digitalWrite (9,OFF); 
  //digitalWrite (RelayPin, OFF); // Uncomment untuk mematikan Relay saat Start awal
  lcd.begin(16,2); // memulai koneksi i2c dengan LCD
  rtc.begin(); // memulai koneksi i2c dengan RTC
  lcd.createChar(0, dgrsChar); //Membuat custom char derajat
  lcd.setCursor (0,0);
  lcd.print(F("  Dani's Timer  "));
  lcd.setCursor (0,1);
  lcd.print(F(" 8Channel Relay "));
  delay (2000);
  lcd.clear();
ReadEeprom();
//Set RTC Untuk Pertama kali
//rtc.setTime (10, 15, 00); 
//rtc.setDate(23, 8, 2016);  
}

void loop()
{
t = rtc.getTime();
Day = rtc.getDOWStr(1);

if (setMode == 0){
hh = t.hour,DEC;
mm = t.min,DEC;
ss = t.sec,DEC;
dd = t.date,DEC;
bb = t.mon,DEC;
yy = t.year,DEC;
}  

  if (setAlarm <2){
  lcd.setCursor(1,0);
  if(setMode==0)lcd.print(Day); else {lcd.print(F("SET"));}
  lcd.print(F(" "));
  if (dd<10){ lcd.print(F("0"));}
  lcd.print(dd); lcd.print(F("-"));
  if (bb<10){ lcd.print(F("0"));} 
  lcd.print(bb); lcd.print(F("-")); 
  lcd.print(yy); lcd.print(F("  ")); 

  lcd.setCursor(0,1); 
  if (hh<10){ lcd.print(F("0"));}
  lcd.print(hh); lcd.print(F(":"));
  if (mm<10){ lcd.print(F("0"));} 
  lcd.print(mm); lcd.print(F(":"));
  if (ss<10){ lcd.print(F("0"));} 
  lcd.print(ss); lcd.print(F(" ")); 
  lcd.print(rtc.getTemp());
  lcd.print((char)0); 
  lcd.print(F("C"));
  lcd.print(F(" ")); 
  }

  blinking();
  setupClock();
  setTimer();
  Timer1 (StartHH, StartMM, FinishHH, FinishMM);
  Timer2 (StartHH2, StartMM2, FinishHH2, FinishMM2);
  Timer3 (StartHH3, StartMM3, FinishHH3, FinishMM3);
  Timer4 (StartHH4, StartMM4, FinishHH4, FinishMM4);
  Timer5 (StartHH5, StartMM5, FinishHH5, FinishMM5);
  Timer6 (StartHH6, StartMM6, FinishHH6, FinishMM6);
  Timer7 (StartHH7, StartMM7, FinishHH7, FinishMM7);
  Timer8 (StartHH8, StartMM8, FinishHH8, FinishMM8);


}

void blinking (){
//BLINKING SCREEN
if (setAlarm <2 && setMode != 0) {delay (100);}
if (setAlarm <2 && setMode == 1){lcd.setCursor(5,0); lcd.print(F("  ")); delay(100);}
if (setAlarm <2 && setMode == 2 && bb>9){lcd.setCursor(8,0); lcd.print(F("  ")); delay(100);}
if (setAlarm <2 && setMode == 2 && bb<=9){lcd.setCursor(8,0); lcd.print(F(" ")); delay(100);}
if (setAlarm <2 && setMode == 3 && bb>9){lcd.setCursor(11,0); lcd.print(F("    ")); delay(100);}
if (setAlarm <2 && setMode == 3 && bb<=9){lcd.setCursor(10,0); lcd.print(F("    ")); delay(100);}
if (setAlarm <2 && setMode == 4){lcd.setCursor(0,1); lcd.print(F("  ")); delay(100);}
if (setAlarm <2 && setMode == 5){lcd.setCursor(3,1); lcd.print(F("  ")); delay(100);}
if (setAlarm <2 && setMode == 6){lcd.setCursor(6,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm != 0  && setAlarm != 1) {delay (100);}
//Relay1
if (setMode == 0 && setAlarm == 2){lcd.setCursor(11,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 3){lcd.setCursor(14,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 4){lcd.setCursor(11,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 5){lcd.setCursor(14,1); lcd.print(F("  ")); delay(100);}
//Relay2
if (setMode == 0 && setAlarm == 6){lcd.setCursor(11,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 7){lcd.setCursor(14,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 8){lcd.setCursor(11,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 9){lcd.setCursor(14,1); lcd.print(F("  ")); delay(100);}
//Relay3
if (setMode == 0 && setAlarm == 10){lcd.setCursor(11,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 11){lcd.setCursor(14,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 12){lcd.setCursor(11,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 13){lcd.setCursor(14,1); lcd.print(F("  ")); delay(100);}
//Relay4
if (setMode == 0 && setAlarm == 14){lcd.setCursor(11,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 15){lcd.setCursor(14,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 16){lcd.setCursor(11,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 17){lcd.setCursor(14,1); lcd.print(F("  ")); delay(100);}
//Relay5
if (setMode == 0 && setAlarm == 18){lcd.setCursor(11,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 19){lcd.setCursor(14,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 20){lcd.setCursor(11,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 21){lcd.setCursor(14,1); lcd.print(F("  ")); delay(100);}
//Relay6
if (setMode == 0 && setAlarm == 22){lcd.setCursor(11,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 23){lcd.setCursor(14,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 24){lcd.setCursor(11,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 25){lcd.setCursor(14,1); lcd.print(F("  ")); delay(100);}
//Relay7
if (setMode == 0 && setAlarm == 26){lcd.setCursor(11,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 27){lcd.setCursor(14,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 28){lcd.setCursor(11,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 29){lcd.setCursor(14,1); lcd.print(F("  ")); delay(100);}
//Relay8
if (setMode == 0 && setAlarm == 30){lcd.setCursor(11,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 31){lcd.setCursor(14,0); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 32){lcd.setCursor(11,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 33){lcd.setCursor(14,1); lcd.print(F("  ")); delay(100);}


}

//Seting Jam ,Tanggal,Alarm/Timer
void setupClock (void) {
   btnUP.read(); 
   btnDN.read();
   btnSET.read();
   btnALR.read();
   
    if (setMode == 7){
    lcd.setCursor (0,0);
    lcd.print (F("Set Date Finish "));
    lcd.setCursor (0,1);
    lcd.print (F("Set Time Finish "));delay (1000);
    rtc.setTime (hh, mm, ss);
    rtc.setDate (dd, bb, yy);  
    lcd.clear();
    setMode = 0;}

    if (setAlarm == 34){
    lcd.setCursor (0,0);
    lcd.print (F("Set Timer Finish"));
    lcd.setCursor (0,1);
    lcd.print (F("-EEPROM Updated-"));
    WriteEeprom();
    delay (2000); lcd.clear();
    setAlarm=0;
    alarmMode=1;}
    
    if (setAlarm >0){ alarmMode=0;}
    
    switch (STATE) {
        
        case WAIT:                            
            if (btnSET.wasPressed())
               { setMode = setMode+1;}
            if (btnALR.wasPressed())
               { setAlarm = setAlarm+1;} 
            if (btnUP.wasPressed())
                STATE = INCR;
            else if (btnDN.wasPressed())
                STATE = DECR;
            else if (btnUP.wasReleased())    
                rpt = REPEAT_FIRST;
            else if (btnDN.wasReleased())
                rpt = REPEAT_FIRST;
            else if (btnUP.pressedFor(rpt)) {  
                rpt += REPEAT_INCR;            
                STATE = INCR;}
            else if (btnDN.pressedFor(rpt)) {
                rpt += REPEAT_INCR;
                STATE = DECR;}
                
            break;

        case INCR:                               
            if (setAlarm<2 && setMode==1 && dd<31)dd=dd+1; 
            if (setAlarm<2 && setMode==2 && bb<12)bb=bb+1;
            if (setAlarm<2 && setMode==3 && yy<2050)yy=yy+1;
            if (setAlarm<2 && setMode==4 && hh<23)hh=hh+1;
            if (setAlarm<2 && setMode==5 && mm<59)mm=mm+1;
            if (setAlarm<2 && setMode==6 && ss<59)ss=ss+1;
            //Relay1
            if (setMode==0 && setAlarm==2 && StartHH<23)StartHH=StartHH+1;
            if (setMode==0 && setAlarm==3 && StartMM<59)StartMM=StartMM+1;
            if (setMode==0 && setAlarm==4 && FinishHH<23)FinishHH=FinishHH+1;
            if (setMode==0 && setAlarm==5 && FinishMM<59)FinishMM=FinishMM+1;
            //Relay2
            if (setMode==0 && setAlarm==6 && StartHH2<23)StartHH2=StartHH2+1;
            if (setMode==0 && setAlarm==7 && StartMM2<59)StartMM2=StartMM2+1;
            if (setMode==0 && setAlarm==8 && FinishHH2<23)FinishHH2=FinishHH2+1;
            if (setMode==0 && setAlarm==9 && FinishMM2<59)FinishMM2=FinishMM2+1;
            //Relay3
            if (setMode==0 && setAlarm==10 && StartHH3<23)StartHH3=StartHH3+1;
            if (setMode==0 && setAlarm==11 && StartMM3<59)StartMM3=StartMM3+1;
            if (setMode==0 && setAlarm==12 && FinishHH3<23)FinishHH3=FinishHH3+1;
            if (setMode==0 && setAlarm==13 && FinishMM3<59)FinishMM3=FinishMM3+1;
            //Relay4
            if (setMode==0 && setAlarm==14 && StartHH4<23)StartHH4=StartHH4+1;
            if (setMode==0 && setAlarm==15 && StartMM4<59)StartMM4=StartMM4+1;
            if (setMode==0 && setAlarm==16 && FinishHH4<23)FinishHH4=FinishHH4+1;
            if (setMode==0 && setAlarm==17 && FinishMM4<59)FinishMM4=FinishMM4+1;
            //Relay5
            if (setMode==0 && setAlarm==18 && StartHH5<23)StartHH5=StartHH5+1;
            if (setMode==0 && setAlarm==19 && StartMM5<59)StartMM5=StartMM5+1;
            if (setMode==0 && setAlarm==20 && FinishHH5<23)FinishHH5=FinishHH5+1;
            if (setMode==0 && setAlarm==21 && FinishMM5<59)FinishMM5=FinishMM5+1;
            //Relay6
            if (setMode==0 && setAlarm==22 && StartHH6<23)StartHH6=StartHH6+1;
            if (setMode==0 && setAlarm==23 && StartMM6<59)StartMM6=StartMM6+1;
            if (setMode==0 && setAlarm==24 && FinishHH6<23)FinishHH6=FinishHH6+1;
            if (setMode==0 && setAlarm==25 && FinishMM6<59)FinishMM6=FinishMM6+1;
            //Relay7
            if (setMode==0 && setAlarm==26 && StartHH7<23)StartHH7=StartHH7+1;
            if (setMode==0 && setAlarm==27 && StartMM7<59)StartMM7=StartMM7+1;
            if (setMode==0 && setAlarm==28 && FinishHH7<23)FinishHH7=FinishHH7+1;
            if (setMode==0 && setAlarm==29 && FinishMM7<59)FinishMM7=FinishMM7+1;
            //Relay8
            if (setMode==0 && setAlarm==30 && StartHH8<23)StartHH8=StartHH8+1;
            if (setMode==0 && setAlarm==31 && StartMM8<59)StartMM8=StartMM8+1;
            if (setMode==0 && setAlarm==32 && FinishHH8<23)FinishHH8=FinishHH8+1;
            if (setMode==0 && setAlarm==33 && FinishMM8<59)FinishMM8=FinishMM8+1;
           
            
            STATE = WAIT;
            break;

        case DECR:                               
            if (setAlarm<2 && setMode==1 && dd>1)dd=dd-1;
            if (setAlarm<2 && setMode==2 && bb>1)bb=bb-1;
            if (setAlarm<2 && setMode==3 && yy>2000)yy=yy-1;
            if (setAlarm<2 && setMode==4 && hh>0)hh=hh-1;
            if (setAlarm<2 && setMode==5 && mm>0)mm=mm-1;
            if (setAlarm<2 && setMode==6 && ss>0)ss=ss-1;
            //Relay1
            if (setMode==0 && setAlarm==2 && StartHH>0)StartHH=StartHH-1;
            if (setMode==0 && setAlarm==3 && StartMM>0)StartMM=StartMM-1;
            if (setMode==0 && setAlarm==4 && FinishHH>0)FinishHH=FinishHH-1;
            if (setMode==0 && setAlarm==5 && FinishMM>0)FinishMM=FinishMM-1;
            //Relay2
            if (setMode==0 && setAlarm==6 && StartHH2>0)StartHH2=StartHH2-1;
            if (setMode==0 && setAlarm==7 && StartMM2>0)StartMM2=StartMM2-1;
            if (setMode==0 && setAlarm==8 && FinishHH2>0)FinishHH2=FinishHH2-1;
            if (setMode==0 && setAlarm==9 && FinishMM2>0)FinishMM2=FinishMM2-1;
            //Relay3
            if (setMode==0 && setAlarm==10 && StartHH3>0)StartHH3=StartHH3-1;
            if (setMode==0 && setAlarm==11 && StartMM3>0)StartMM3=StartMM3-1;
            if (setMode==0 && setAlarm==12 && FinishHH3>0)FinishHH3=FinishHH3-1;
            if (setMode==0 && setAlarm==13 && FinishMM3>0)FinishMM3=FinishMM3-1;
            //Relay4
            if (setMode==0 && setAlarm==14 && StartHH4>0)StartHH4=StartHH4-1;
            if (setMode==0 && setAlarm==15 && StartMM4>0)StartMM4=StartMM4-1;
            if (setMode==0 && setAlarm==16 && FinishHH4>0)FinishHH4=FinishHH4-1;
            if (setMode==0 && setAlarm==17 && FinishMM4>0)FinishMM4=FinishMM4-1;
            //Relay5
            if (setMode==0 && setAlarm==18 && StartHH5>0)StartHH5=StartHH5-1;
            if (setMode==0 && setAlarm==19 && StartMM5>0)StartMM5=StartMM5-1;
            if (setMode==0 && setAlarm==20 && FinishHH5>0)FinishHH5=FinishHH5-1;
            if (setMode==0 && setAlarm==21 && FinishMM5>0)FinishMM5=FinishMM5-1;
            //Relay6
            if (setMode==0 && setAlarm==22 && StartHH6>0)StartHH6=StartHH6-1;
            if (setMode==0 && setAlarm==23 && StartMM6>0)StartMM6=StartMM6-1;
            if (setMode==0 && setAlarm==24 && FinishHH6>0)FinishHH6=FinishHH6-1;
            if (setMode==0 && setAlarm==25 && FinishMM6>0)FinishMM6=FinishMM6-1;
            //Relay7
            if (setMode==0 && setAlarm==26 && StartHH7>0)StartHH7=StartHH7-1;
            if (setMode==0 && setAlarm==27 && StartMM7>0)StartMM7=StartMM7-1;
            if (setMode==0 && setAlarm==28 && FinishHH7>0)FinishHH7=FinishHH7-1;
            if (setMode==0 && setAlarm==29 && FinishMM7>0)FinishMM7=FinishMM7-1;
            //Relay8
            if (setMode==0 && setAlarm==30 && StartHH8>0)StartHH8=StartHH8-1;
            if (setMode==0 && setAlarm==31 && StartMM8>0)StartMM8=StartMM8-1;
            if (setMode==0 && setAlarm==32 && FinishHH8>0)FinishHH8=FinishHH8-1;
            if (setMode==0 && setAlarm==33 && FinishMM8>0)FinishMM8=FinishMM8-1;
         
            STATE = WAIT;
            break;
    }
}

void Timer1 (uint8_t StartHH, uint8_t StartMM,uint8_t FinishHH, uint8_t FinishMM) { 
  //Timer ON 
 if (alarmMode==1 && hh >= StartHH && mm>=StartMM) { 
    digitalWrite(2, ON);
 }
 //Timer OFF
  if (alarmMode==1 && hh>=FinishHH && mm>=FinishMM ){
 digitalWrite(2, OFF);
 //alarmMode = 0;
 }
}
void Timer2 (uint8_t StartHH2, uint8_t StartMM2,uint8_t FinishHH2, uint8_t FinishMM2) { 
  //Timer ON 
 if (alarmMode==1 && hh >= StartHH2 && mm>=StartMM2) { 
    digitalWrite(3, ON);
 }
 //Timer OFF
  if (alarmMode==1 && hh>=FinishHH2 && mm>=FinishMM2 ){
 digitalWrite(3, OFF);
 //alarmMode = 0;
 }
}
void Timer3 (uint8_t StartHH3, uint8_t StartMM3,uint8_t FinishHH3, uint8_t FinishMM3) { 
  //Timer ON 
 if (alarmMode==1 && hh >= StartHH3 && mm>=StartMM3) { 
    digitalWrite(4, ON);
 }
 //Timer OFF
  if (alarmMode==1 && hh>=FinishHH3 && mm>=FinishMM3 ){
 digitalWrite(4, OFF);
 //alarmMode = 0;
 }
}
void Timer4 (uint8_t StartHH4, uint8_t StartMM4,uint8_t FinishHH4, uint8_t FinishMM4) { 
  //Timer ON 
 if (alarmMode==1 && hh >= StartHH4 && mm>=StartMM4) { 
    digitalWrite(5, ON);
 }
 //Timer OFF
  if (alarmMode==1 && hh>=FinishHH4 && mm>=FinishMM4 ){
 digitalWrite(5, OFF);
 //alarmMode = 0;
 }
}
void Timer5 (uint8_t StartHH5, uint8_t StartMM5,uint8_t FinishHH5, uint8_t FinishMM5) { 
  //Timer ON 
 if (alarmMode==1 && hh >= StartHH5 && mm>=StartMM5) { 
    digitalWrite(6, ON);
 }
 //Timer OFF
  if (alarmMode==1 && hh>=FinishHH5 && mm>=FinishMM5 ){
 digitalWrite(6, OFF);
 //alarmMode = 0;
 }
}
void Timer6 (uint8_t StartHH6, uint8_t StartMM6,uint8_t FinishHH6, uint8_t FinishMM6) { 
  //Timer ON 
 if (alarmMode==1 && hh >= StartHH6 && mm>=StartMM6) { 
    digitalWrite(7, ON);
 }
 //Timer OFF
  if (alarmMode==1 && hh>=FinishHH6 && mm>=FinishMM6 ){
 digitalWrite(7, OFF);
 //alarmMode = 0;
 }
}
void Timer7 (uint8_t StartHH7, uint8_t StartMM7,uint8_t FinishHH7, uint8_t FinishMM7) { 
  //Timer ON 
 if (alarmMode==1 && hh >= StartHH7 && mm>=StartMM7) { 
    digitalWrite(8, ON);
 }
 //Timer OFF
  if (alarmMode==1 && hh>=FinishHH7 && mm>=FinishMM7 ){
 digitalWrite(8, OFF);
 //alarmMode = 0;
 }
}
void Timer8 (uint8_t StartHH8, uint8_t StartMM8,uint8_t FinishHH8, uint8_t FinishMM8) { 
  //Timer ON 
 if (alarmMode==1 && hh >= StartHH8 && mm>=StartMM8) { 
    digitalWrite(9, ON);
 }
 //Timer OFF
  if (alarmMode==1 && hh>=FinishHH8 && mm>=FinishMM8 ){
 digitalWrite(9, OFF);
 //alarmMode = 0;
 }
}

void setTimer (){
  //Relay1
 if (setMode == 0 && setAlarm !=0 && setAlarm !=1 && setAlarm >=2 && setAlarm <=5 ){
  lcd.setCursor (0,0);
  lcd.print(F("Ch1 Start :"));
  lcd.setCursor (11,0);
  if(StartHH<10){lcd.print(F("0"));}
  lcd.print (StartHH); lcd.print(F(":"));
  if(StartMM<10){lcd.print(F("0"));}
  lcd.print (StartMM); 

  lcd.setCursor (0,1);
  lcd.print(F("Ch1 Finish:"));
  lcd.setCursor (11,1);
  if(FinishHH<10){lcd.print(F("0"));}
  lcd.print (FinishHH); lcd.print(F(":"));
  if(FinishMM<10){lcd.print(F("0"));}
  lcd.print (FinishMM); 
 }
//Relay2
 if (setMode == 0 && setAlarm !=0 && setAlarm !=1 && setAlarm >=6 && setAlarm <=9 ){
  lcd.setCursor (0,0);
  lcd.print(F("Ch2 Start :"));
  lcd.setCursor (11,0);
  if(StartHH2<10){lcd.print(F("0"));}
  lcd.print (StartHH2); lcd.print(F(":"));
  if(StartMM2<10){lcd.print(F("0"));}
  lcd.print (StartMM2); 

  lcd.setCursor (0,1);
  lcd.print(F("Ch2 Finish:"));
  lcd.setCursor (11,1);
  if(FinishHH2<10){lcd.print(F("0"));}
  lcd.print (FinishHH2); lcd.print(F(":"));
  if(FinishMM2<10){lcd.print(F("0"));}
  lcd.print (FinishMM2); 
 }
//Relay3
 if (setMode == 0 && setAlarm !=0 && setAlarm !=1 && setAlarm >=10 && setAlarm <=13 ){
  lcd.setCursor (0,0);
  lcd.print(F("Ch3 Start :"));
  lcd.setCursor (11,0);
  if(StartHH3<10){lcd.print(F("0"));}
  lcd.print (StartHH3); lcd.print(F(":"));
  if(StartMM3<10){lcd.print(F("0"));}
  lcd.print (StartMM3); 

  lcd.setCursor (0,1);
  lcd.print(F("Ch3 Finish:"));
  lcd.setCursor (11,1);
  if(FinishHH3<10){lcd.print(F("0"));}
  lcd.print (FinishHH3); lcd.print(F(":"));
  if(FinishMM3<10){lcd.print(F("0"));}
  lcd.print (FinishMM3); 
 }
//Relay4
 if (setMode == 0 && setAlarm !=0 && setAlarm !=1 && setAlarm >=14 && setAlarm <=17 ){
  lcd.setCursor (0,0);
  lcd.print(F("Ch4 Start :"));
  lcd.setCursor (11,0);
  if(StartHH4<10){lcd.print(F("0"));}
  lcd.print (StartHH4); lcd.print(F(":"));
  if(StartMM4<10){lcd.print(F("0"));}
  lcd.print (StartMM4); 

  lcd.setCursor (0,1);
  lcd.print(F("Ch4 Finish:"));
  lcd.setCursor (11,1);
  if(FinishHH4<10){lcd.print(F("0"));}
  lcd.print (FinishHH4); lcd.print(F(":"));
  if(FinishMM4<10){lcd.print(F("0"));}
  lcd.print (FinishMM4); 
 }
//Relay5
 if (setMode == 0 && setAlarm !=0 && setAlarm !=1 && setAlarm >=18 && setAlarm <=21 ){
  lcd.setCursor (0,0);
  lcd.print(F("Ch5 Start :"));
  lcd.setCursor (11,0);
  if(StartHH5<10){lcd.print(F("0"));}
  lcd.print (StartHH5); lcd.print(F(":"));
  if(StartMM5<10){lcd.print(F("0"));}
  lcd.print (StartMM5); 

  lcd.setCursor (0,1);
  lcd.print(F("Ch5 Finish:"));
  lcd.setCursor (11,1);
  if(FinishHH5<10){lcd.print(F("0"));}
  lcd.print (FinishHH5); lcd.print(F(":"));
  if(FinishMM5<10){lcd.print(F("0"));}
  lcd.print (FinishMM5); 
 }
//Relay6
 if (setMode == 0 && setAlarm !=0 && setAlarm !=1 && setAlarm >=22 && setAlarm <=25 ){
  lcd.setCursor (0,0);
  lcd.print(F("Ch6 Start :"));
  lcd.setCursor (11,0);
  if(StartHH6<10){lcd.print(F("0"));}
  lcd.print (StartHH6); lcd.print(F(":"));
  if(StartMM6<10){lcd.print(F("0"));}
  lcd.print (StartMM6); 

  lcd.setCursor (0,1);
  lcd.print(F("Ch6 Finish:"));
  lcd.setCursor (11,1);
  if(FinishHH6<10){lcd.print(F("0"));}
  lcd.print (FinishHH6); lcd.print(F(":"));
  if(FinishMM6<10){lcd.print(F("0"));}
  lcd.print (FinishMM6); 
 }
//Relay7
 if (setMode == 0 && setAlarm !=0 && setAlarm !=1 && setAlarm >=26 && setAlarm <=29 ){
  lcd.setCursor (0,0);
  lcd.print(F("Ch7 Start :"));
  lcd.setCursor (11,0);
  if(StartHH7<10){lcd.print(F("0"));}
  lcd.print (StartHH7); lcd.print(F(":"));
  if(StartMM7<10){lcd.print(F("0"));}
  lcd.print (StartMM7); 

  lcd.setCursor (0,1);
  lcd.print(F("Ch7 Finish:"));
  lcd.setCursor (11,1);
  if(FinishHH7<10){lcd.print(F("0"));}
  lcd.print (FinishHH7); lcd.print(F(":"));
  if(FinishMM7<10){lcd.print(F("0"));}
  lcd.print (FinishMM7); 
 }
//Relay8
 if (setMode == 0 && setAlarm !=0 && setAlarm !=1 && setAlarm >=30 && setAlarm <=33 ){
  lcd.setCursor (0,0);
  lcd.print(F("Ch8 Start :"));
  lcd.setCursor (11,0);
  if(StartHH8<10){lcd.print(F("0"));}
  lcd.print (StartHH8); lcd.print(F(":"));
  if(StartMM8<10){lcd.print(F("0"));}
  lcd.print (StartMM8); 

  lcd.setCursor (0,1);
  lcd.print(F("Ch8 Finish:"));
  lcd.setCursor (11,1);
  if(FinishHH8<10){lcd.print(F("0"));}
  lcd.print (FinishHH8); lcd.print(F(":"));
  if(FinishMM8<10){lcd.print(F("0"));}
  lcd.print (FinishMM8); 
 }
}

void ReadEeprom () {
  StartHH=EEPROM.read(1);
  StartMM=EEPROM.read(2);
  FinishHH=EEPROM.read(3);
  FinishMM=EEPROM.read(4);

  StartHH2=EEPROM.read(5);
  StartMM2=EEPROM.read(6);
  FinishHH2=EEPROM.read(7);
  FinishMM2=EEPROM.read(8);

  StartHH3=EEPROM.read(9);
  StartMM3=EEPROM.read(10);
  FinishHH3=EEPROM.read(11);
  FinishMM3=EEPROM.read(12);
    
  StartHH4=EEPROM.read(13);
  StartMM4=EEPROM.read(14);
  FinishHH4=EEPROM.read(15);
  FinishMM4=EEPROM.read(16);

  StartHH5=EEPROM.read(17);
  StartMM5=EEPROM.read(18);
  FinishHH5=EEPROM.read(19);
  FinishMM5=EEPROM.read(20);

  StartHH6=EEPROM.read(21);
  StartMM6=EEPROM.read(22);
  FinishHH6=EEPROM.read(23);
  FinishMM6=EEPROM.read(24);

  StartHH7=EEPROM.read(25);
  StartMM7=EEPROM.read(26);
  FinishHH7=EEPROM.read(27);
  FinishMM7=EEPROM.read(28);

  StartHH8=EEPROM.read(29);
  StartMM8=EEPROM.read(30);
  FinishHH8=EEPROM.read(31);
  FinishMM8=EEPROM.read(32);
  
}

void WriteEeprom () {
  EEPROM.write(1,StartHH);
  EEPROM.write(2,StartMM);
  EEPROM.write(3,FinishHH);
  EEPROM.write(4,FinishMM);

  EEPROM.write(5,StartHH2);
  EEPROM.write(6,StartMM2);
  EEPROM.write(7,FinishHH2);
  EEPROM.write(8,FinishMM2);

  EEPROM.write(9,StartHH3);
  EEPROM.write(10,StartMM3);
  EEPROM.write(11,FinishHH3);
  EEPROM.write(12,FinishMM3);

  EEPROM.write(13,StartHH4);
  EEPROM.write(14,StartMM4);
  EEPROM.write(15,FinishHH4);
  EEPROM.write(16,FinishMM4);

  EEPROM.write(17,StartHH5);
  EEPROM.write(18,StartMM5);
  EEPROM.write(19,FinishHH5);
  EEPROM.write(20,FinishMM5);

  EEPROM.write(21,StartHH6);
  EEPROM.write(22,StartMM6);
  EEPROM.write(23,FinishHH6);
  EEPROM.write(24,FinishMM6);

  EEPROM.write(25,StartHH7);
  EEPROM.write(26,StartMM7);
  EEPROM.write(27,FinishHH7);
  EEPROM.write(28,FinishMM7);

  EEPROM.write(29,StartHH8);
  EEPROM.write(30,StartMM8);
  EEPROM.write(31,FinishHH8);
  EEPROM.write(32,FinishMM8);
}
