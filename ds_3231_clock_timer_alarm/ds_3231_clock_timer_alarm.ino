///////////////////////////////////////////////
// Coding ini dibuat Oleh Dani Rajacell ///////
// Untuk www.belajarduino.com /////////////////
// Support by www.tokopedia.com/rajacell //////
// Copyright 24/8/2016 Rev.0.0 ////////////////
///////////////////////////////////////////////

#include <DS3231.h> //Memanggil RTC3231 Library
#include <Wire.h>  // i2C Conection Library
#include <LiquidCrystal_I2C.h>  //Memanggil i2C LCD Library
#include <Button.h> //Memanggil library Push Button

//Setup Tombol Setting
#define DN_PIN 2 //Decrease Button
#define UP_PIN 3 //Increase Button
#define SET_PIN 4  //Setup Button
#define ALR_PIN 5  //Setup Button
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
///////////////////////////////////////////////
// Coding ini dibuat Oleh Dani Rajacell ///////
// Untuk www.belajarduino.com /////////////////
// Support by www.tokopedia.com/rajacell //////
// Copyright 24/8/2016 Rev.0.0 ////////////////
///////////////////////////////////////////////
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//custom degrees char
uint8_t dgrsChar[8] = {0x4,0xa,0x4,0x0,0x0,0x0,0x0,0x0}; 

// Init DS3231
DS3231  rtc(SDA, SCL);

// Init a Time-data structure
Time  t; //pencacah string time()

uint32_t targetTime = 0;
uint8_t conv2d(const char* p) {
uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
   v = *p - '0';
  return 10 * v + *++p - '0';}

//Mengambil waktu jam dari waktu Compile/Upload di system Windows
uint8_t hh = 0, mm = 0, ss = 0, dd = 0, bb = 0;
int yy = 0;
String Day = "  ";
uint8_t alarmHH = 9, alarmMM = 30;
int alarmLONG = 5;
uint8_t setMode = 0, setAlarm = 0, alarmMode=0;


void setup()
{
  // Setup Serial connection
  //Serial.begin(115200);
  pinMode (13, OUTPUT); 
  //digitalWrite (13, LOW); // jika menggunakan relay sebagai beban alarm
  lcd.begin(16,2); // memulai koneksi i2c dengan LCD
  rtc.begin(); // memulai koneksi i2c dengan RTC
  lcd.createChar(0, dgrsChar); //Membuat custom char derajat
  lcd.setCursor (0,0);
  lcd.print(F("  Dani's Clock  "));
  lcd.setCursor (0,1);
  lcd.print(F("With RTC DS3231"));
  delay (2000);
  lcd.clear();

//rtc.setTime (10, 15, 00); 
//rtc.setDate(23, 8, 2016);  
}

///////////////////////////////////////////////
// Coding ini dibuat Oleh Dani Rajacell ///////
// Untuk www.belajarduino.com /////////////////
// Support by www.tokopedia.com/rajacell //////
// Copyright 24/8/2016 Rev.0.0 ////////////////
///////////////////////////////////////////////

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
  lcd.print(dd); lcd.print(F("-")); 
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
  
  setupClock();
  Alarm (alarmHH, alarmMM, alarmLONG);

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
//if (setMode == 0 && setAlarm == 1){lcd.clear(); lcd.setCursor(3,0); lcd.print(F("Alarm OFF")); delay(100);}
if (setMode == 0 && setAlarm == 2){lcd.setCursor(0,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 3){lcd.setCursor(3,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 4 && alarmLONG >9){lcd.setCursor(12,1); lcd.print(F("  ")); delay(100);}
if (setMode == 0 && setAlarm == 4 && alarmLONG <10){lcd.setCursor(12,1); lcd.print(F(" ")); delay(100);}

Serial.print (setMode);
Serial.print ("  ");
Serial.println (setAlarm);
}
///////////////////////////////////////////////
// Coding ini dibuat Oleh Dani Rajacell ///////
// Untuk www.belajarduino.com /////////////////
// Support by www.tokopedia.com/rajacell //////
// Copyright 24/8/2016 Rev.0.0 ////////////////
///////////////////////////////////////////////
void setupClock (void) {
   btnUP.read();                             //read the buttons
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

    if (setAlarm == 5){
    lcd.setCursor (0,0);
    lcd.print (F("Set Alarm Finish"));
    lcd.setCursor (0,1);
    lcd.print (F("Alarm at : "));
    lcd.print (alarmHH); lcd.print (F(":"));
    lcd.print (alarmMM); 
    delay (1000); lcd.clear();
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
                STATE = INCR;
            }
            else if (btnDN.pressedFor(rpt)) {
                rpt += REPEAT_INCR;
                STATE = DECR;
            }
            break;

        case INCR:                               
            if (setAlarm<2 && setMode==1 && dd<31)dd=dd+1; 
            if (setAlarm<2 && setMode==2 && bb<12)bb=bb+1;
            if (setAlarm<2 && setMode==3 && yy<2050)yy=yy+1;
            if (setAlarm<2 && setMode==4 && hh<23)hh=hh+1;
            if (setAlarm<2 && setMode==5 && mm<59)mm=mm+1;
            if (setAlarm<2 && setMode==6 && ss<59)ss=ss+1;
            if (setMode==0 && setAlarm==2 && alarmHH<23)alarmHH=alarmHH+1;
            if (setMode==0 && setAlarm==3 && alarmMM<59)alarmMM=alarmMM+1;
            if (setMode==0 && setAlarm==4 && alarmLONG<59)alarmLONG=alarmLONG+1;
            STATE = WAIT;
            break;

        case DECR:                               
            if (setAlarm<2 && setMode==1 && dd>0)dd=dd-1;
            if (setAlarm<2 && setMode==2 && bb>0)bb=bb-1;
            if (setAlarm<2 && setMode==3 && yy>2000)yy=yy-1;
            if (setAlarm<2 && setMode==4 && hh>0)hh=hh-1;
            if (setAlarm<2 && setMode==5 && mm>0)mm=mm-1;
            if (setAlarm<2 && setMode==6 && ss>0)ss=ss-1;  
            if (setMode==0 && setAlarm==2 && alarmHH>0)alarmHH=alarmHH-1;
            if (setMode==0 && setAlarm==3 && alarmMM>0)alarmMM=alarmMM-1;
            if (setMode==0 && setAlarm==4 && alarmLONG>0)alarmLONG=alarmLONG-1;
            STATE = WAIT;
            break;
    }
}
///////////////////////////////////////////////
// Coding ini dibuat Oleh Dani Rajacell ///////
// Untuk www.belajarduino.com /////////////////
// Support by www.tokopedia.com/rajacell //////
// Copyright 24/8/2016 Rev.0.0 ////////////////
///////////////////////////////////////////////
void Alarm (uint8_t alarmHH, uint8_t alarmMM,int alarmLONG) {

 if (alarmMode==1 && hh == alarmHH && (mm - alarmMM >= 0 ) && (mm - alarmMM <= alarmLONG )) {
  tone (13, 1200);
  
  if(ss%2==0){lcd.noBacklight();}
  else {lcd.backlight ();}
  
  btnALR.read();
  if (btnALR.wasPressed())
 { alarmMode = 0; lcd.backlight();}}
 
 
 else {noTone (13);  lcd.backlight();}

 if (setMode == 0 && setAlarm !=0 && setAlarm !=1){
  lcd.setCursor (1,0);
  lcd.print(F("  Set Alarm    "));
  lcd.setCursor (0,1);
  if(alarmHH<10){lcd.print(F("0"));}
  lcd.print (alarmHH); lcd.print(F(":"));
  if(alarmMM<10){lcd.print(F("0"));}
  lcd.print (alarmMM); lcd.print(F("  Long:"));
  lcd.print (alarmLONG); lcd.print(F("mnt "));
 }
}
