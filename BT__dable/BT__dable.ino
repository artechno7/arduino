/*
    Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.
    NOTE:
    1)For Arduino Mega Connect Bluetooth on Serial3 pins.
    2)For Arduino Uno/Nano library uses SoftwareSerial,hence pin 2 and pin 3 are used
    as RX and TX pins respectively on SoftwareSerial.Hence with arduino Uno
    follow below connections for bluetooth.
    UNO  - BLUETOOTH
    2    - TX
    3    - RX
    3)For Uno/Nano keep bluetooth Baudrate below 38400.

    You can reduce the size of library compiled by enabling only those modules that you want to
    use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

    Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

const int Left = 4;
const int Right = 5;

const int Forward = 6;
const int Backward = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);
  Dabble.begin(9600);  //Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.

  pinMode(Forward, OUTPUT);
  pinMode(Left, OUTPUT);
  pinMode(Backward, OUTPUT);
  pinMode(Right, OUTPUT);
}

void loop() {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.      //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("UP");
  }
  else if ((GamePad.isLeftPressed())&&(GamePad.isTrianglePressed()))
  {
    Serial.print("Belok kiri jalan");
    kiri();
    maju();
  }

   else if ((GamePad.isRightPressed())&&(GamePad.isTrianglePressed()))
  {
    Serial.print("Belok kanan jalan");
    kanan();
    maju();
  }

  else if ((GamePad.isRightPressed())&&(GamePad.isCrossPressed()))
  {
    Serial.print("Belok kanan mundur");
    kanan();
    mundur();
  }
  else if ((GamePad.isLeftPressed())&&(GamePad.isCrossPressed()))
  {
    Serial.print("Belok kiri mundur");
    kiri();
    mundur();
  }
  else if (GamePad.isDownPressed())
  {
    Serial.print("DOWN");
  }

  else if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
    kiri();
  }

  else if (GamePad.isRightPressed())
  {
    Serial.print("Right");
    kanan();
  }

  else if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  else if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
  }

  else if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
    mundur();
  }

  else if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
    maju();
  }

  else if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  else if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
  }
  else 
  {
     Serial.println("berhenti");
            berhenti();
           }
  
  /*
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getx_axis();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.gety_axis();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
  */
}

void berhenti ()
{
  digitalWrite(Forward,LOW);
    digitalWrite(Right,LOW);
    digitalWrite(Left,LOW);
    digitalWrite(Backward,LOW);
}

void kanan ()
{
digitalWrite(Left,LOW);
    digitalWrite(Right,HIGH);
}

void kiri ()
{
digitalWrite(Left,HIGH);
    digitalWrite(Right,LOW);
}

void maju ()
{
  digitalWrite(Forward,HIGH);
    digitalWrite(Backward,LOW);
}

void mundur ()
{
  digitalWrite(Forward,LOW);
    digitalWrite(Backward,HIGH);
}
