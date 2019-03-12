//----

// motor[index] = speed
int16_t motor[2] = {100, 100};
#define RIGHT 0
#define LEFT 1

// led[index] = {R,G,B}
uint8_t led[1][3];

// ultrasonik[index] = jarak
uint8_t ultrasonik[1];

// ultrasonik_digital[index] = true|false
int ultrasonik_digital[1];
// ultrasonik_threshold[index] = threshold jarak untuk digital reading
uint8_t ultrasonik_threshold[1];

// ldr[index] = intensitas cahaya
uint8_t ldr[2];
// ldr_digital[index] = true|false
uint8_t ldr_digital[2];
// ldr_threshold[index] = threshold jarak untuk digital reading
uint8_t ldr_threshold[2] = {50, 50};

// buzzer[index] = freq
int sBuzzer[1];

void getFirmwareVersion();
void motors();
void leds();
void ldrs();
void ultrasoniks();

void old_function();
void set_speed();
void s_delay_ms();
void line_follower();

//----

void init_sirobo_android() {
  android.pushRegHandler(getFirmwareVersion);
  android.pushRegHandler(motors);
  android.pushRegHandler(leds);
  android.pushRegHandler(ultrasoniks);
  android.pushRegHandler(ldrs);

  android.pushStoredFunc(old_function);
  android.pushStoredFunc(set_speed);
  android.pushStoredFunc(s_delay_ms);
  android.pushStoredFunc(line_follower);
}

void ldrs() {
  uint8_t side = android.getByte();

  if (android.getWriteAccess() == false) {
    //read request
    uint8_t in_analog = android.getByte();
    ldr[RIGHT] = analogRead(pinLdr1) / 4;
    ldr[LEFT] = analogRead(pinLdr2) / 4;

    if (in_analog) {

    } else {
      if (side != 0) {
        ldr_digital[side - 1] = (ldr[side - 1] < ldr_threshold[side - 1] ? 1 : 0);

        android.putByte(side);
        android.putByte(ldr_digital[side - 1]);
      } else {
        ldr_digital[RIGHT] = (ldr[RIGHT] < ldr_threshold[RIGHT] ? 1 : 0);
        ldr_digital[LEFT] = (ldr[LEFT] < ldr_threshold[LEFT] ? 1 : 0);

        android.putByte(side);
        android.putByte(ldr_digital[RIGHT] & ldr_digital[LEFT] ? 1 : 0);
      }
    }
  } else {
    //write operation
  }
}

void ultrasoniks() {
  uint8_t sensor_num = android.getByte();

  if (android.getWriteAccess() == false) {
    //read request
    uint8_t in_analog = android.getByte();

    uint8_t sensor_jarak = (uint8_t) jarak;
//    Serial.print(jarak);
//    Serial.println();
//    Serial.print(sensor_jarak);
//    Serial.println();
    android.putByte(1);
    android.putByte(sensor_jarak);
  } else {
    //write operation
  }
}

void getFirmwareVersion() {
  char firmwareVer[] = "SiRobo v1.1";

  if (android.getWriteAccess() == false) {
    //read request
    android.putString(firmwareVer);
  }
}

void motors() {
  uint8_t targetMotor = android.getByte();

  if (android.getWriteAccess() == false) {
    //read request
    android.putInt8(targetMotor);
    android.putInt16(motor[targetMotor]);
  } else {
    //write operation
    int16_t mSpeed = android.getInt16();
    motor[targetMotor] = mSpeed;
    android.putInt8(targetMotor);
    android.putInt8(1);
  }
}

void leds() {
  uint8_t side = android.getByte();

  if (android.getWriteAccess() == false) {
    //read request
  }
  else {
    //write operation
    uint8_t red = android.getByte();
    uint8_t green = android.getByte();
    uint8_t blue = android.getByte();

    rgbLED.setColor(side, red, green, blue);
    rgbLED.show();

    android.putByte(side);
    android.putByte(1);
  }
}

/*
   Stored Functions...
*/

/*
   Fungsi untuk menangani protokol awal SiRobo
   @param bt(1) - perintah dari android
   @return byte(1) - 1 (true)
*/
void old_function() {
  uint8_t bt = android.getByte();
  switch (bt)
  {
    case 0x00 :
      calcMotorSpeed(1);
      rgbLED.setColor(0, 0, 0, 0);
      rgbLED.show();
      noTone(pinBuzzer);
      setMotor(0, 0);
      error = 0;
      robotSpeedGain = 1 ;
      break;

    case 0x01 :
      setMotor(0, 0);
      break;

    case 0x02 :
      setMotor(motorSpeed, motorSpeed);
      break;

    case 0x03:
      setMotor(-motorSpeed, -motorSpeed);
      break;

    case 0x04:
      setMotor(motorSpeed, -motorSpeed);
      break;

    case 0x05:
      setMotor(-motorSpeed, motorSpeed);
      break;

    case 0x06 :
      setMotor(motorSpeed , motorSpeed / 2);
      break;

    case 0x07 :
      setMotor(motorSpeed / 2, motorSpeed);
      break;

    case 0x08:
      setMotor(-motorSpeed, -motorSpeed / 2);
      break;

    case 0x09:
      setMotor(-motorSpeed / 2, -motorSpeed );
      break;

    case 0x0A:
      // GRIPPER ON
      //      stateServo = 0x0A;
      //      if (cekStateServo != stateServo)
      //      {
      //        servo1.writeMicroseconds(1500 + bawah);
      //        servo2.writeMicroseconds(1500 + buka);
      //        delay(700);
      //        servo1.writeMicroseconds(1500 + bawah);
      //        servo2.writeMicroseconds(1500 + tutup);
      //        delay(700);
      //        cekStateServo = stateServo;
      //      }
      //      servo1.writeMicroseconds(1500 + atas);
      //      servo2.writeMicroseconds(1500 + tutup);
      break;

    case 0x0B:
      // GRIPPER OFF
      //      stateServo = 0x0b ;
      //      if (cekStateServo != stateServo)
      //      {
      //        servo1.writeMicroseconds(1500 + bawah);
      //        servo2.writeMicroseconds(1500 + tutup);
      //        delay(700);
      //        servo1.writeMicroseconds(1500 + bawah);
      //        servo2.writeMicroseconds(1500 + buka);
      //        delay(700);
      //        cekStateServo = stateServo;
      //      }
      //      servo1.writeMicroseconds(1500 + atas);
      //      servo2.writeMicroseconds(1500 + buka);
      break;

    case 0x0C:
      // BUZZER ON
      buzzer.mainkanMusik(buzzer.Size(1), Tune1, Beat1);
      break;

    case 0x0D:
      // BUZZER OFF
      break;

    case 0x0E:
      rgbLED.setColor(0, 255, 0, 0);
      rgbLED.show();
      break;

    case 0x0F:
      rgbLED.setColor(0, 0, 0, 0);
      rgbLED.show();
      break;

    case 0x10:
      rgbLED.setColor(0, 0, 255, 0);
      rgbLED.show();
      break;

    case 0x11:
      rgbLED.setColor(0, 0, 0, 0);
      rgbLED.show();
      break;

    case 0x12:
      rgbLED.setColor(0, 0, 0, 255);
      rgbLED.show();
      break;

    case 0x13:
      rgbLED.setColor(0, 0, 0, 0);
      rgbLED.show();
      break;

    default :
      if (bt >= 0x14 && bt <= 0x1D) {
        calcMotorSpeed((int) bt - (int) 0x13);
      }
      break;

    case 30: noTone(pinBuzzer); break;
    case 31: tone(pinBuzzer, NOTE_C4); break;
    case 32: tone(pinBuzzer, NOTE_D4); break;
    case 33: tone(pinBuzzer, NOTE_E4); break;
    case 34: tone(pinBuzzer, NOTE_F4); break;
    case 35: tone(pinBuzzer, NOTE_G4); break;
    case 36: tone(pinBuzzer, NOTE_A4); break;
    case 37: tone(pinBuzzer, NOTE_B4); break;
    case 38: tone(pinBuzzer, NOTE_C5); break;
    case 39: tone(pinBuzzer, NOTE_D5); break;
    case 40: tone(pinBuzzer, NOTE_E5); break;
    case 41: tone(pinBuzzer, NOTE_F5); break;
    case 42: tone(pinBuzzer, NOTE_G5); break;
    case 43: tone(pinBuzzer, NOTE_A5); break;
    case 44: tone(pinBuzzer, NOTE_B5); break;
    case 45: tone(pinBuzzer, NOTE_C6); break;
    case 46: tone(pinBuzzer, NOTE_D6); break;
    case 47: tone(pinBuzzer, NOTE_E6); break;
    case 48: tone(pinBuzzer, NOTE_F6); break;
    case 49: tone(pinBuzzer, NOTE_G6); break;
    case 50: tone(pinBuzzer, NOTE_A6); break;
    case 51: tone(pinBuzzer, NOTE_B6); break;
  }

  android.putByte(1);
}

/*
   Fungsi motor maju
*/
void set_speed() {
  int16_t rightSpeed = android.getInt16();
  int16_t leftSpeed = android.getInt16();

  motor[LEFT] = calcMotorSpeed(leftSpeed);
  motor[RIGHT] = calcMotorSpeed(rightSpeed);

  setMotor(motor[LEFT], motor[RIGHT]);

  android.putByte(1);
}

void line_follower() {
#define SIDE_BOTH 0
#define SIDE_RIGHT 1
#define SIDE_LEFT 2

#define MOVE_FORWARD 0
#define MOVE_RIGHT 1
#define MOVE_LEFT 2
#define MOVE_STOP 3

  uint8_t side = android.getByte();
  uint8_t movement = android.getByte();

  //---pathplan di sini

  pathPlan(side, movement);
  //---end

  // kasih tau android sudah selesai
  android.putByte(1);
}

/*
   Fungsi delay
*/
void s_delay_ms() {
  int16_t ms = android.getInt16();

  delay(ms);

  android.putByte(1);
}
