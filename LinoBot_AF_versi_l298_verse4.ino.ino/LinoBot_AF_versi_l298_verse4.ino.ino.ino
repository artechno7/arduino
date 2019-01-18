
#define lefts A4 
#define rights A5 


//motor Speed
int HighSpeed = 140; //max 255 std HML 110 90 70 HS 160 100 80
int MidSpeed = 120; //best 170 120 90
int LowSpeed = 120;
int SpeedDelay = 20;



// L298N Control Pins
const int MotorKiriMaju = 5;
const int MotorKiriMundur = 4;
const int MotorKananMaju = 3;
const int MotorKananMundur = 2;
const int SpeedKiri = 9;
const int SpeedKanan = 10;


void setup() {
  pinMode(MotorKananMundur,OUTPUT);
  pinMode(MotorKananMaju,OUTPUT); //mo ka maju
  pinMode(MotorKiriMundur,OUTPUT);
  pinMode(MotorKiriMaju,OUTPUT); //mo ki maju
  
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
  //begin serial communication
  Serial.begin(9600);
  
}

void maju()
{
  digitalWrite(MotorKiriMaju,HIGH);
  digitalWrite(MotorKananMaju,HIGH);
  digitalWrite(MotorKananMundur,LOW);
  digitalWrite(MotorKiriMundur,LOW);
  analogWrite (SpeedKiri, HighSpeed);
  analogWrite (SpeedKanan, HighSpeed);
  //delay(SpeedDelay);
}

void mundur()
{
  digitalWrite(MotorKiriMundur,HIGH);
  digitalWrite(MotorKananMundur,HIGH);
  digitalWrite(MotorKiriMaju,LOW);
  digitalWrite(MotorKananMaju,LOW);
  analogWrite (SpeedKiri, HighSpeed);
  analogWrite (SpeedKanan, HighSpeed);
}

void kanan()
{
  digitalWrite(MotorKiriMaju,HIGH);
  digitalWrite(MotorKananMundur,HIGH);
  digitalWrite(MotorKananMaju,LOW);
  digitalWrite(MotorKiriMundur,LOW);
  analogWrite (SpeedKiri, MidSpeed);
  analogWrite (SpeedKanan, LowSpeed);
  //delay(SpeedDelay);
}

void kiri()
{
  digitalWrite(MotorKananMaju,HIGH);
  digitalWrite(MotorKiriMundur,HIGH);
  digitalWrite(MotorKiriMaju,LOW);
  digitalWrite(MotorKananMundur,LOW);
  analogWrite (SpeedKiri, LowSpeed);
  analogWrite (SpeedKanan, MidSpeed);
  //delay(SpeedDelay);
}

void berhenti()
{
  digitalWrite(MotorKananMaju,LOW);
  digitalWrite(MotorKiriMundur,LOW);
  digitalWrite(MotorKiriMaju,LOW);
  digitalWrite(MotorKananMundur,LOW);
}

void loop(){
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(lefts));
  Serial.println(analogRead(rights));

  //line detected by both
  if(analogRead(lefts)<=300 && analogRead(rights)<=300){
    //stop
    maju();
  }
  
  //line detected by left sensor
  else if(analogRead(lefts)<=300 && !analogRead(rights)<=300){
    //turn left
    kanan();
  }

  //line detected by right sensor
  else if(!analogRead(lefts)<=300 && analogRead(rights)<=300){
    //turn right
    kiri();
  }

  //line detected by none
  else if(!analogRead(lefts)<=300 && !analogRead(rights)<=300){
    //stop
    berhenti();
  
  }
  
}


