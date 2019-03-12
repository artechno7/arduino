#include "SiRobo.h"
#include <EEPROM.h>

#define invertMotorKiri
#define invertMotorKanan

int ePeka[4] = {
  1, 2, 3, 4
}
;

unsigned long
millisIr = 0 ,
previousMillis = 0,
interval = 3500
           ;

char
pinMotorKiriMaju    = 6,
pinMotorKiriMundur  = 7,
pinMotorKananMaju   = 5,
pinMotorKananMundur = 4,
pinUltraSonic  = 10,
pinSound  = 2,
pinBuzzer = 3,
pinServo1 = 8,
pinServo2 = 9,
pinLed  = 13,
pinIR   = 12,
pinSw   = 11,
pinS0   = A2,
pinS1   = A3,
pinS2   = A6,
pinS3   = A7,
pinLdr1 = A1,
pinLdr2 = A0;


char buff[100];

//hitam 240
//putih 70
//peka = putih + ((hitam-putih)/2)
int peka[4] = {90, 90, 90, 90}
              , pekaMax[4], pekaMin[4];
float
moveControl,
kp = 15, //KP
kd = 5,   //KD
lastError = 0,
lastError2 = 0,
lastError3 = 0,
error = 0,
rate,
robotSpeedGain = 1,
alpha = 0.95,
jarakRaw,
jarak
;

char
cekAksiPathPlan = 3
                  ;

int
PWMA,
PWMB,
PWMAin,
PWMBin,
speed,
statusSensor,
state,
sensorBit,
adc_sensor[4],
sendat[4],
//SPEED RANGE 0-255
robotSpeedForward,
robotSpeedForwardSlow,
robotSpeedBackward,
robotSpeedBackwardStop,
x, i,
stateLine = 2,
maxpwm = 250,
robotSpeedRight,
robotSpeedLeft,
robotSpeed = 70,  //SPEED RANGE 0-255
t,
countPing,
timeSlot
;

//Sensor Ultrasonic
const int pingPin = 10;
int indexPing;

#define bawah 550
#define atas -480
#define buka 150
#define tutup -150

//#include <Servo.h>

//Servo servo1, servo2; // create servo object to control a servo
int val1, val2, stateServo = 0, cekStateServo = 0;

#define sw !digitalRead(pinSw)

int
dataAn, dataAnO,
        dataInt[4], data[4];
unsigned char
dataRx = 0,
countRx = 0,
countRxProtokol = 0,
dataMasuk[8]
;

//BT
char bt;
int dataSensor[5];

int motorSpeed = 175;

int calcMotorSpeed(int speedLevel) {
  motorSpeed = speedLevel * 255 / 10;
  return motorSpeed;
}

//void init_sirobo_android();

SiRoboAndroid android(&Serial);
SiRGBLed rgbLED(pinLed, 2);
SiBuzzer buzzer(pinBuzzer);

void setup() {
  //serial
  Serial.begin(9600);
  init_sirobo_android();

  Timer1.initialize(10);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(servisInterupsi);  // attaches callback() as a timer overflow interrupt

  //  ir.begin();

  //sensor
  pinMode(pinS0, INPUT);
  pinMode(pinS1, INPUT);
  pinMode(pinS2, INPUT);
  pinMode(pinS3, INPUT);
  pinMode(pinLdr1, INPUT);
  pinMode(pinLdr2, INPUT);
  pinMode(pinSw, INPUT_PULLUP);
  pinMode(pinSound, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  //motor
  pinMode(pinMotorKiriMaju, OUTPUT);
  pinMode(pinMotorKiriMundur, OUTPUT);
  pinMode(pinMotorKananMaju, OUTPUT);
  pinMode(pinMotorKananMundur, OUTPUT);

  //  servo1.attach(pinServo1);
  //  servo2.attach(pinServo2);
  //  servo1.writeMicroseconds(1500 + atas);
  //  servo2.writeMicroseconds(1500 + buka);

  //  rgbLED.setColor(0, 150, 0, 0);
  //  delay(500);
  //  rgbLED.setColor(0, 0, 150, 0);
  //  delay(500);
  //  rgbLED.setColor(0, 0, 0, 150);
  //  delay(500);
  //
  
  rgbLED.setColor(0, 0, 0, 0);
  rgbLED.show();
  buzzer.mainkanMusik(buzzer.Size(1), Tune1, Beat1);

  //  oled.drawBmp(sirobo);
  for (x = 1; x <= 4; x++)
  {
    rgbLED.setColor(0, 100, 0, 0);
    rgbLED.show();
    tone(pinBuzzer, NOTE_C4);
    delay(50);
    rgbLED.setColor(0, 0, 100, 0);
    rgbLED.show();
    tone(pinBuzzer, NOTE_E4);
    delay(50);
    rgbLED.setColor(0, 0, 0, 100);
    rgbLED.show();
    tone(pinBuzzer, NOTE_F4);
    delay(50);
  }

  rgbLED.setColor(0, 0, 0, 0);
  rgbLED.show();
  noTone(pinBuzzer);
  error = 0;
  robotSpeedGain = 1 ;

  robotSpeedForward = 220;
  robotSpeedForwardSlow = 200;
  robotSpeedBackward = -150;
  robotSpeedBackwardStop = -100;

  //play();//Play the music.
  //  for (x = 0; x <= 20; x++)
  //  {
  //    if (sw)
  //    {
  //      calibration();
  //      break;
  //    }
  //    delay(50);
  //  }

  state = 5  ;

  //display.drawBitmap(0, 0, desy, 128, 64, 1);
  //display.display();
  //display.startscrollleft(0, 7);
}

void loop() {
  switch (state)
  {
    case 11:
      setMotor(250, 250); delay(1500);
      setMotor(-250, -250); delay(1500);
      setMotor(0, 0); delay(1500);
      break;
    case 0:
      sprintf(buff, "Menu || ");
      Serial.print(buff);
      setMotor(0, 0);
      readSensor();
      bacaSensorJarak();
      delay(10);
      sprintf(buff, "%3d %3d %3d %3d || %d%d%d%d || %d %d", adc_sensor[3], adc_sensor[2], adc_sensor[1], adc_sensor[0], sendat[3], sendat[2], sendat[1], sendat[0] , stateLine, jarak );
      Serial.print(buff);
      Serial.println();
      if (sw)
      {
        state = 5;
        for (x = 1; x <= 1; x++)
        {
          buzzer.setBuzzerTone(NOTE_D4, 250);
          delay(200);
        }
      }
      //      if (Serial.available())
      //      {
      //        bt = Serial.read();
      //        if (bt >= 1)
      //        {
      //          state = 5;
      //        }
      //      }
      break;

    case 1:
      //oled.displayStr(0, 25, "Line");
      //      sprintf(buff, "Line  || %3d", robotSpeed);
      //      Serial.println(buff);

      robotSpeed = 80 ;
      kp = 15;
      kd = 5;
      //bacaSensorJarak();
      follow_line();

      if (sw)
      {
        state = 2;
        for (x = 1; x <= 2; x++)
        {
          buzzer.setBuzzerTone(NOTE_E4, 250);
          delay(200);
        }
      }
      break;
    case 2:
      //oled.displayStr(0, 25, "Light");
      sprintf(buff, "Light  || ");
      Serial.print(buff);
      followLight();
      if (sw)
      {
        state = 3;
        for (x = 1; x <= 3; x++)
        {
          buzzer.setBuzzerTone(NOTE_E4, 250);
          delay(200);
        }
      }
      break;

    case 3:
      //oled.displayStr(0, 25, "Avoider");
      sprintf(buff, "Avoider  || ");
      Serial.print(buff);
      avoider();
      if (sw)
      {
        state = 5;
        setMotor(0, 0);
        rgbLED.setColor(0, 0, 0, 0);
        rgbLED.show();
        delay(100);
        buzzer.setBuzzerTone(NOTE_E4, 250);
        delay(1000);
      }
      break;

    case 5:
      //sprintf(buff, "BT || ");
      //Serial.print(buff);
      //bluetooth();

      //      if ( (millis() - millisIr) >= 200) {
      //        Serial.println("Stop");
      //        setMotor(0, 0);
      //      }

      //      if (ir.decode())
      //      {
      //        //        millisIr = millis();
      //        switch (ir.value)
      //        {
      //          case 0xB847FF00 : dataIr = "menu"; break;
      //          case 0xBA45FF00 : dataIr = "power"; break;
      //          case 0xBB44FF00 : dataIr = "test"; break;
      //          case 0xBC43FF00 : dataIr = "back"; break;
      //          case 0xBF40FF00 : dataIr = "+"; setMotor(motorSpeed, motorSpeed);  break;
      //          case 0xF807FF00 : dataIr = "kiri"; setMotor(-motorSpeed, motorSpeed);  break;
      //          case 0xF609FF00 : dataIr = "kanan"; setMotor(motorSpeed, -motorSpeed);  break;
      //          case 0xEA15FF00 : dataIr = "play"; break;
      //          case 0xE619FF00 : dataIr = "-"; setMotor(-motorSpeed, -motorSpeed); break;
      //          case 0xF20DFF00 : dataIr = "c"; setMotor(0, 0); break;
      //          case 0xE916FF00 : dataIr = "0"; calcMotorSpeed(0); break;
      //          case 0xF30CFF00 : dataIr = "1"; calcMotorSpeed(1); break;
      //          case 0xE718FF00 : dataIr = "2"; calcMotorSpeed(2); break;
      //          case 0xA15EFF00 : dataIr = "3"; calcMotorSpeed(3); break;
      //          case 0xF708FF00 : dataIr = "4"; calcMotorSpeed(4); break;
      //          case 0xE31CFF00 : dataIr = "5"; calcMotorSpeed(5); break;
      //          case 0xA55AFF00 : dataIr = "6"; calcMotorSpeed(6); break;
      //          case 0xBD42FF00 : dataIr = "7"; calcMotorSpeed(7); break;
      //          case 0xAD52FF00 : dataIr = "8"; calcMotorSpeed(8); break;
      //          case 0xB54AFF00 : dataIr = "9"; calcMotorSpeed(9); break;
      //        }
      //        Serial.println(dataIr);
      //      }

      //Serial.print(bt," ");
      //oled.displayStr(0, 25, "Bluetooth");
      terimaDataArif();
      if (sw)
      {
        state = 1;
        for (x = 1; x <= 1; x++)
        {
          buzzer.setBuzzerTone(NOTE_E4, 250);
          delay(500);
        }
      }
      break;

    case 6:
      pathPlan(3, 1);
      pathPlan(3, 3);
      pathPlan(3, 2);
      pathPlan(3, 3);
      pathPlan(3, 3);
      pathPlan(3, 1);

      setMotor(0, 0);
      rgbLED.setColor(0, 0, 0, 0);
      rgbLED.show();
      noTone(pinBuzzer);

      state = 5;
      break;
      
    case 7:
      Serial.print(jarak);
      Serial.println();
      break;
  }
}

void tandaDeteksi()
{
  tone(pinBuzzer, NOTE_C5, 200);
  statusSensor = 1;
}
void selesaiTandaDeteksi()
{
  noTone(pinBuzzer);
}

void pathPlan(int pilihanSensor, int aksi)
{
  statusSensor = 0;
  robotSpeed = 20 ;
  kp = 20;
  kd = 3;
  previousMillis = millis();
  while (1)
  {
    if (cekAksiPathPlan == 0 | cekAksiPathPlan == 3) break;
    follow_line();
    if (millis() - previousMillis >= 200) break;
  }
  robotSpeed = 70 ;
  kp = 8;
  kd = 3;
  while (1)
  {
    follow_line();
    switch (pilihanSensor) {
      case 0 : //kiri&kanan
        if (sendat[3] == 1 & sendat[0] == 1)tandaDeteksi();
        break;
      case 1 : //kanan
        if (sendat[0] == 1)tandaDeteksi();
        break;
      case 2 : //kiri
        if (sendat[3] == 1)tandaDeteksi();
        break;
      case 3 : //kiri/kanan
        if (sendat[3] == 1 | sendat[0] == 1) tandaDeteksi();
        break;
    }
    if (statusSensor == 1)
      break;
  }
  statusSensor = 0;
  switch (aksi) {
    case 0 : //maju
      setMotor(robotSpeed, robotSpeed);
      delay(100);
      cekAksiPathPlan = 0 ;
      break;
    case 1 : //kanan
      setMotor(-50, -50);
      delay(20);
      while (1)
      {
        readSensor();
        if (sendat[0] == 0)break;
        setMotor(70, 70);
        delay(10);
      }
      setMotor(70, 70);
      delay(80);
      while (1)
      {
        readSensor();
        if (sendat[0] == 1)break;
        setMotor(60, -80);
        delay(10);
      }
      cekAksiPathPlan = 1 ;
      break;
    case 2 : //kiri
      setMotor(-50, -50);
      delay(20);
      while (1)
      {
        readSensor();
        if (sendat[3] == 0)break;
        setMotor(70, 70);
        delay(10);
      }
      setMotor(70, 70);
      delay(80);
      while (1)
      {
        readSensor();
        if (sendat[3] == 1)break;
        setMotor(-80, 60);
        delay(10);
      }
      cekAksiPathPlan = 2 ;
      break;
    case 3 : //stop
      setMotor(0, 0);
      cekAksiPathPlan = 3 ;
      break;
  }
}

//void callback()
//{
//  setMotorIn();
//}

void pv() {
  switch (sensorBit) {
    //    case  0b1110: error = -3; break;
    //    case  0b1100: error = -3; break;
    //    case  0b0011: error = 3; break;
    //    case  0b0111: error = 3; break;
    //    case  0b1110:
    //      rgbLED.setColor(1, 0, 0, 0);
    //      rgbLED.setColor(2, 100, 0, 100);
    //      rgbLED.show();
    //      robotSpeedGain = 1 ;
    //      error = -3; break;
    case  0b1000:
      rgbLED.setColor(1, 0, 0, 0);
      rgbLED.setColor(2, 100, 0, 100);
      rgbLED.show();
      robotSpeedGain = 1 ;
      error = -3; break;
    case  0b0100:
      rgbLED.setColor(1, 0, 0, 0);
      rgbLED.setColor(2, 0, 100, 0);
      rgbLED.show();
      robotSpeedGain = 1 ;
      error = -1; break;
    //       ||
    case  0b0110:
      rgbLED.setColor(1, 0, 100, 0);
      rgbLED.setColor(2, 0, 100, 0);
      rgbLED.show();
      robotSpeedGain = 1 ;
      error = 0;
      break;
    //       ||
    case  0b0010:
      rgbLED.setColor(1, 0, 100, 0);
      rgbLED.setColor(2, 0, 0, 0);
      rgbLED.show();
      robotSpeedGain = 1 ;
      error = 1; break;
    case  0b0001:
      rgbLED.setColor(1, 100, 0, 100);
      rgbLED.setColor(2, 0, 0, 0);
      rgbLED.show();
      robotSpeedGain = 1 ;
      error = 3; break;
    //    case  0b0111:
    //      rgbLED.setColor(1, 100, 0, 100);
    //      rgbLED.setColor(2, 0, 0, 0);
    //      rgbLED.show();
    //      robotSpeedGain = 1 ;
    //      error = 3; break;
    default:
      if (lastError == -3 | lastError == -1 )
      {
        rgbLED.setColor(1, 0, 0, 0);
        rgbLED.setColor(2, 0, 100, 100);
        rgbLED.show();
        robotSpeedGain = 1 ;
        error = -1.5 ;
      }
      //      else if (lastError2 == -4 & lastError == -3 )
      //      {
      //        rgbLED.setColor(1, 0, 0, 0);
      //        rgbLED.setColor(2, 0, 100, 100);
      //        rgbLED.show();
      //        robotSpeedGain = 1 ;
      //        error = -2 ;
      //      }
      //      else if ( (lastError2 == 0 & lastError == -3) | (lastError2 == -1 & lastError == -3) | (lastError2 == -2 & lastError == -3))
      //      {
      //        rgbLED.setColor(1, 0, 0, 0);
      //        rgbLED.setColor(2, 100, 0, 0);
      //        rgbLED.show();
      //        robotSpeedGain = 0.6 ;
      //        error = -4 ;
      //      }
      else if (lastError == 3 | lastError == 1 )
      {
        rgbLED.setColor(1, 0, 100, 100);
        rgbLED.setColor(2, 0, 0, 0);
        rgbLED.show();
        robotSpeedGain = 1 ;
        error = 1.5 ;
      }
      //      else if (lastError2 == 4 & lastError == 3 )
      //      {
      //        rgbLED.setColor(1, 0, 100, 100);
      //        rgbLED.setColor(2, 0, 0, 0);
      //        rgbLED.show();
      //        robotSpeedGain = 1 ;
      //        error = 2 ;
      //      }
      //      else if ( (lastError2 == 0 & lastError == 3) | (lastError2 == 1 & lastError == 3) | (lastError2 == 2 & lastError == 3))
      //      {
      //        rgbLED.setColor(1, 100, 0, 0);
      //        rgbLED.setColor(2, 0, 0, 0);
      //        rgbLED.show();
      //        robotSpeedGain = 0.6 ;
      //        error = 4 ;
      //      }
      else
      {
        error = lastError;
      }
      break;
  }
}

void follow_line() {
  readSensor();
  pv();

  if (error != lastError)
  {
    lastError2 = lastError;
  }

  rate = error - lastError;

  lastError = error ;
  moveControl = (kp * error) + (rate * kd);

  //  sprintf(buff, "%d | %d | %d", error, lastError, lastError2);
  //  Serial.println(buff);

  robotSpeedRight = (int)((robotSpeed * robotSpeedGain) - moveControl);
  robotSpeedLeft  = (int)((robotSpeed * robotSpeedGain) + moveControl);

  setMotor(robotSpeedLeft, robotSpeedRight);
}

void followLight() {
  adc_sensor[0] = analogRead(pinLdr1) / 4 ;
  adc_sensor[1] = analogRead(pinLdr2) / 4 ;
  for (x = 0; x <= 1; x++)
  {
    if (adc_sensor[x] < 50)
      sendat[x] = 1;
    else
      sendat[x] = 0;
  }
  if (sendat[1] == 1 & sendat[0] == 1)
  {
    rgbLED.setColor(1, 0, 100, 0);
    rgbLED.setColor(2, 0, 100, 0);
    rgbLED.show();
    setMotor(robotSpeed, robotSpeed);
  }
  else if (sendat[1] == 0 & sendat[0] == 1)
  {
    rgbLED.setColor(1, 100, 100, 0);
    rgbLED.setColor(2, 0, 0, 0);
    rgbLED.show();
    setMotor(robotSpeed, -robotSpeed);
  }
  else if (sendat[1] == 1 & sendat[0] == 0)
  {
    rgbLED.setColor(1, 0, 0, 0);
    rgbLED.setColor(2, 100, 100, 0);
    rgbLED.show();
    setMotor(-robotSpeed, robotSpeed);
  }
}

void calibration()
{
  setMotor(robotSpeedForward, -robotSpeedForward);
  for (x = 0; x < 4; x++)
  {
    pekaMax[x] = 0;
    pekaMin[x] = 255;
  }

  previousMillis = millis();
  while (1)
  {
    if (millis() - previousMillis >= interval) break;
    adc_sensor[0] = analogRead(pinS0) / 4 ;
    adc_sensor[1] = analogRead(pinS1) / 4 ;
    adc_sensor[2] = analogRead(pinS2) / 4 ;
    adc_sensor[3] = analogRead(pinS3) / 4 ;

    sprintf(buff, "%3d %3d %3d %3d ", adc_sensor[3], adc_sensor[2], adc_sensor[1], adc_sensor[0]);
    Serial.println(buff);

    for (x = 0; x <= 3; x++)
    {
      if (adc_sensor[x] > pekaMax[x])
        pekaMax[x] = adc_sensor[x];

      if (adc_sensor[x] < pekaMin[x])
        pekaMin[x] = adc_sensor[x];
    }
  }

  setMotor(0, 0);
  for (x = 0; x <= 3; x++)
  {
    peka[x] = ((pekaMax[x] - pekaMin[x]) / 1.7) + pekaMin[x];
    EEPROM.write(ePeka[x], peka[x]);
  }

  sprintf(buff, "%3d %3d %3d %3d || ", pekaMax[3], pekaMax[2], pekaMax[1], pekaMax[0]);
  Serial.print(buff);
  sprintf(buff, "%3d %3d %3d %3d || ",  pekaMin[3], pekaMin[2],  pekaMin[1], pekaMin[0]);
  Serial.print(buff);
  sprintf(buff, "%3d %3d %3d %3d ",  peka[3], peka[2],  peka[1], peka[0]);
  Serial.println(buff);
}

void readSensor() {
  adc_sensor[0] = analogRead(pinS0) / 4 ;
  adc_sensor[1] = analogRead(pinS1) / 4 ;
  adc_sensor[2] = analogRead(pinS2) / 4 ;
  adc_sensor[3] = analogRead(pinS3) / 4 ;
  for (x = 0; x <= 3; x++)
  {
    if (adc_sensor[x] > peka[x])
      sendat[x] = 1;
    else
      sendat[x] = 0;
  }
  sensorBit = 0;
  for (x = 0; x <= 3; x++) {
    sensorBit += sendat[x] * (1 << x);
  }
  delay(5);
  //  sprintf(buff, "%3d %3d %3d %3d || ", adc_sensor[3], adc_sensor[2], adc_sensor[1], adc_sensor[0]);
  //  Serial.print(buff);
  //  sprintf(buff, "%d%d%d%d %3d", sendat[3], sendat[2], sendat[1], sendat[0], sensorBit);
  //  Serial.println(buff);
}


void avoider()
{
  bacaSensorJarak();
  delay(10);
  robotSpeed = 170;
  if (jarak <= 15)
  {
    rgbLED.setColor(0, 100, 0, 0);
    rgbLED.show();
    setMotor(0, 0);
    delay(1000);
    setMotor(robotSpeed * 0.8, -robotSpeed * 0.8);
    delay(600);
  }
  else if (jarak <= 40)
  {
    rgbLED.setColor(0, 0, 0, 100);
    rgbLED.show();
    setMotor(robotSpeed * 0.8, robotSpeed * 0.8);
  }
  else
  {
    rgbLED.setColor(0, 0, 100, 0);
    rgbLED.show();
    setMotor(robotSpeed, robotSpeed);
  }
}

void bacaSensorJarak()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  delayMicroseconds(50);
  jarakRaw = 0;
  for (indexPing = 0; indexPing <= 200; indexPing++)
  {
    if (digitalRead(pingPin)) jarakRaw++;
    delayMicroseconds(57);
  }
  jarak = ((1 - alpha) * jarak) + (alpha * jarakRaw);
}

void servisInterupsi()
{
  switch (timeSlot)
  {
    case 0:
      pinMode(pingPin, OUTPUT);
      digitalWrite(pingPin, HIGH);
      Timer1.setPeriod(10);
      timeSlot = 1;
      break;
    case 1:
      digitalWrite(pingPin, LOW);
      pinMode(pingPin, INPUT);
      Timer1.setPeriod(600);
      countPing = 0;
      jarakRaw = 0;
      timeSlot = 2;
      break;
    case 2:
      if (digitalRead(pingPin))
      {
        jarakRaw++;
      }
      Timer1.setPeriod(57);
      countPing++;
      if (countPing > 200)
      {
//        errorDistance1 = abs(distance - lastDistance[5]);
//        for (in = 5; in > 0; in--)
//        {
//          lastDistance[in] = lastDistance[in - 1];
//        }
//        lastDistance[0] = distance;
//
//        if (errorDistance1 < 5 )
//          dataSensor[0] = distance;
//        else
//          dataSensor[0] = lastDistance[5];

        jarak = ((1 - alpha) * jarak) + (alpha * jarakRaw);

        Timer1.setPeriod(10000);
        timeSlot = 0;
        setMotorIn();
        break ;
      }
  }
}

void setMotor(int speedA, int speedB)
{
  PWMA = speedA;
  if (PWMA > maxpwm)      // A
    PWMA = maxpwm;
  else if (PWMA < -maxpwm)
    PWMA = -maxpwm;

  PWMB = speedB;
  if (PWMB > maxpwm)     // B
    PWMB = maxpwm;
  else if (PWMB < -maxpwm)
    PWMB = -maxpwm;

  //  sprintf(buff, "                  %3d %3d ", PWMAin, PWMBin);
  //  Serial.println(buff);
}

void setMotorIn()
{
  int PWMSwitch = 120;

  if (PWMA > 0)
  {
    if (PWMAin < 0 ) PWMAin = 0;
    else if (PWMA < PWMSwitch ) PWMAin = PWMA;
    else if (PWMAin < PWMA & PWMAin < PWMSwitch) PWMAin += 5;
    else PWMAin = PWMA;
  }
  else if (PWMA < 0)
  {
    if (PWMAin > 0 ) PWMAin = 0;
    else if (PWMA > -PWMSwitch ) PWMAin = PWMA;
    else if (PWMAin > PWMA & PWMAin > -PWMSwitch) PWMAin -= 5;
    else PWMAin = PWMA;
  }
  else
  {
    PWMAin = PWMA;
  }

  //  if (-PWMSwitch <= PWMA & PWMA <= PWMSwitch)
  //  {
  //    PWMAin = PWMA;
  //  }
  //  else if ( PWMA > PWMSwitch)
  //  {
  //    if ( PWMAin < PWMA & PWMAin < PWMSwitch)PWMAin = PWMSwitch;
  //    else if (PWMAin < PWMA) PWMAin += 2;
  //    else if (PWMAin >= PWMA)  PWMAin = PWMA;
  //  }
  //  else if ( PWMA < -PWMSwitch)
  //  {
  //    if ( PWMAin > PWMA & PWMAin > -PWMSwitch)PWMAin = -PWMSwitch;
  //    else if (PWMAin > PWMA) PWMAin -= 2;
  //    else if (PWMAin <= PWMA)  PWMAin = PWMA;
  //  }

#ifdef invertMotorKiri
  if (PWMAin < 0) {         //A
    analogWrite(pinMotorKiriMaju, -PWMAin);
    digitalWrite(pinMotorKiriMundur, LOW);
  }
  else {
    analogWrite(pinMotorKiriMaju, 255 - PWMAin);
    digitalWrite(pinMotorKiriMundur, HIGH);
  }
#else
  if (PWMAin < 0) {         //A
    analogWrite(pinMotorKiriMaju, 255 + PWMAin);
    digitalWrite(pinMotorKiriMundur, HIGH);
  }
  else {
    analogWrite(pinMotorKiriMaju, PWMAin);
    digitalWrite(pinMotorKiriMundur, LOW);
  }
#endif

  if (PWMB > 0)
  {
    if (PWMBin < 0 ) PWMBin = 0;
    else if (PWMB < PWMSwitch ) PWMBin = PWMB;
    else if (PWMBin < PWMB & PWMBin < PWMSwitch) PWMBin += 5;
    else PWMBin = PWMB;
  }
  else if (PWMB < 0)
  {
    if (PWMBin > 0 ) PWMBin = 0;
    else if (PWMB > -PWMSwitch ) PWMBin = PWMB;
    else if (PWMBin > PWMB & PWMBin > -PWMSwitch) PWMBin -= 5;
    else PWMBin = PWMB;
  }
  else
  {
    PWMBin = PWMB;
  }

  //  if (-PWMSwitch <= PWMB & PWMB <= PWMSwitch)
  //  {
  //    PWMBin = PWMB;
  //  }
  //  else if ( PWMB > PWMSwitch)
  //  {
  //    if ( PWMBin < PWMB & PWMBin < PWMSwitch)PWMBin = PWMSwitch;
  //    else if (PWMBin < PWMB) PWMBin += 2;
  //    else if (PWMBin >= PWMB)  PWMBin = PWMB;
  //  }
  //  else if ( PWMB < -PWMSwitch)
  //  {
  //    if ( PWMBin > PWMB & PWMBin > -PWMSwitch)PWMBin = -PWMSwitch;
  //    else if (PWMBin > PWMB) PWMBin -= 2;
  //    else if (PWMBin <= PWMB)  PWMBin = PWMB;
  //  }

#ifdef invertMotorKanan
  if (PWMBin < 0) {         //B
    analogWrite(pinMotorKananMaju, -PWMBin);
    digitalWrite(pinMotorKananMundur, LOW);
  }
  else {
    analogWrite(pinMotorKananMaju, 255 - PWMBin);
    digitalWrite(pinMotorKananMundur, HIGH);
  }
#else
  if (PWMBin < 0) {         //B
    analogWrite(pinMotorKananMaju, 255 + PWMBin);
    digitalWrite(pinMotorKananMundur, HIGH);
  }
  else {
    analogWrite(pinMotorKananMaju, PWMBin);
    digitalWrite(pinMotorKananMundur, LOW);
  }
#endif

}

void terimaDataArif() {
  android.handleAndroidData();
}
