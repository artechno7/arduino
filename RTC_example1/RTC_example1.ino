// FAR TOO SIMPLE SCHEDULER 1.0
// andrevergamito, 26/8/2015

#include <Wire.h>               // essential libraries needed for the project IF you intend on using a rtc      and a lcd display
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

RTC_DS1307 rtc;                 // declare RTC
LiquidCrystal_I2C lcd(0x27, 20, 4);   // address column and rows of the i2c LCD

bool stat1;     //4 booleans to store in the eeprom the current state of the lighs
bool stat2;
bool stat3;
bool stat4;


#define RELAY1  2    //BLU                //output pins for four relays used to control the lights    
#define RELAY2  3    //VER                    
#define RELAY3  4    //ROS                    
#define RELAY4  5    //BIA


int luce1 = 0;  //BLU                   //current state of the lights
int luce2 = 0;  //VER
int luce3 = 0;  //ROS
int luce4 = 0;  //BIA


//ORE ACCENSIONE                          // hour and minutes the four schedulers are going to turn on
int ore1on = 10; //BLU
int min1on = 0;
int ore2on = 10; //VER
int min2on = 30;
int ore3on = 11; //ROS
int min3on = 0;
int ore4on = 12; //BIA
int min4on = 0;

//ORE SPEGNIMENTO

int ore1off = 13; //BLU                   // hour and minutes the four schedulers are going to turn off
int min1off = 0;
int ore2off = 13; //VER
int min2off = 30;
int ore3off = 13; //ROS
int min3off = 0;
int ore4off = 13; //BIA
int min4off = 30;


void setup () {

  stat1 = EEPROM.read(0);         // pull the eeprom-saved data when turning on to get the lights to the status previus to turning off and than on again the arduino
  stat2 = EEPROM.read(1);
  stat3 = EEPROM.read(2);
  stat4 = EEPROM.read(3);


  luce1 = stat1;                  // every light now gets the eeprom vallue just fetched
  luce2 = stat2;
  luce3 = stat3;
  luce4 = stat4;

  Wire.begin();                   // start i2c communication, turn on screen bachlight and clear the LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();

  pinMode(RELAY1, OUTPUT);       //set the four relays pins as output
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  digitalWrite(RELAY1, HIGH);     //turn all the light of for now to prevent random switches while code loads
  digitalWrite(RELAY2, HIGH);
  digitalWrite(RELAY3, HIGH);
  digitalWrite(RELAY4, HIGH);



  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));         //uncomment to set RTC time as of sketch compiling time BUT then upload code with line blanked out to prevent clock resetting time

  Serial.begin(9600);
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));

}

}


void loop () {

  DateTime now = rtc.now();       //pull RTC data
  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  //ORE
  lcd.setCursor(0, 0);
  lcd.print("  :  :      /  /");                            ///////////////////////////     Example 20x4 layout
  lcd.setCursor(0, 0);                                   //00:00:00 00/00/0000 /
  lcd.print(now.hour());                                //                             /
  lcd.setCursor(3, 0);                                   //BLU  VER  ROS  BIA  /
  lcd.print(now.minute());                             //OFF  ON   OFF  ON    /
  lcd.setCursor(6, 0);                                   ///////////////////////////
  lcd.print(now.second());
  lcd.setCursor(10, 0);
  lcd.print(now.day());
  lcd.setCursor(13, 0);
  lcd.print(now.month());
  lcd.setCursor(16, 0);
  lcd.print(now.year());

  lcd.setCursor(0, 2);
  lcd.print("BLU  VER  ROS  BIA");

  //ATTENTION: this is the part of code where is decided what happens when a time is met and where the on/off on the screen is decided

  lcd.setCursor(0, 3);                        // luce1
  if (luce1 == 0) {                           // if luce1 is marked as off (0)
    lcd.print("OFF");                          //print OFF on the LCD
    EEPROM.update(0, 0);                  //and write this value on eeprom. i  used update because in this way if previous value == new value no writing occurs saving eeprom cycles but wasting 3.3ms

    digitalWrite(RELAY1, HIGH);         //if the light is off the relay is high, that is because if i lose power all light go on and i can manually control them

  }
  else {                                         //if luce1 is marked as On (1)
    lcd.print("ON ");                         //print ON on the LCD
    EEPROM.update(0, 1);                 //and write this value on eeprom
    digitalWrite(RELAY1, LOW);          //also turn on the light
  }

  lcd.setCursor(5, 3);          // luce2
  if (luce2 == 0) {
    lcd.print("OFF");
    EEPROM.update(1, 0);
    digitalWrite(RELAY2, HIGH);
  }
  else {
    lcd.print("ON ");
    EEPROM.update(1, 1);
    digitalWrite(RELAY2, LOW);
  }

  lcd.setCursor(10, 3);          // luce3
  if (luce3 == 0) {
    lcd.print("OFF");
    EEPROM.update(2, 0);
    digitalWrite(RELAY3, HIGH);
  }
  else {
    lcd.print("ON ");
    EEPROM.update(2, 1);
    digitalWrite(RELAY3, LOW);
  }

  lcd.setCursor(15, 3);          // luce4
  if (luce4 == 0) {
    lcd.print("OFF");
    EEPROM.update(3, 0);
    digitalWrite(RELAY4, HIGH);
  }
  else {
    lcd.print("ON ");
    EEPROM.update(3, 1);
    digitalWrite(RELAY4, LOW);
  }

  // IMPORTANT!!! this is the bit of code actually imporant, where time is checked every second and switches are pulled on/off

  int hour = now.hour();    //make the hours and minutes int to prevent error with 0 being seen as error
  int minute = now.minute();

  //turning on sequence

  if (hour == ore1on) {             //if hours match turning on time and minutes too, flag luce1 so next cycle magic can happen
    if (minute == min1on) luce1 = 1;
  }

  if (hour == ore2on) {
    if (minute == min2on) luce2 = 1;
  }

  if (hour == ore3on) {
    if (minute == min3on) luce3 = 1;
  }

  if (hour == ore4on) {
    if (minute == min4on) luce4 = 1;
  }

  //turning off sequence
  if (hour == ore1off) {
    if (minute == min1off) luce1 = 0;
  }

  if (hour == ore2off) {
    if (minute == min2off) luce2 = 0;
  }

  if (hour == ore3off) {
    if (minute == min3off) luce3 = 0;
  }

  if (hour == ore4off) {
    if (minute == min4off) luce4 = 0;
  }

  delay(900); //this delay keeps the code running almost once a second, to prevent too fast refreshes of the LCD
}
