
#define lefts A4 
#define rights A5 


//motor Speed
int HighSpeed = 140; //max 255 std HML 110 90 70 HS 160 100 80
int MidSpeed = 120;
int LowSpeed = 120;
int SpeedDelay = 20;
int stop_distance = 12;



// L298N Control Pins
const int MotorKiriMaju = 5;
const int MotorKiriMundur = 4;
const int MotorKananMaju = 3;
const int MotorKananMundur = 2;
const int SpeedKiri = 9;
const int SpeedKanan = 10;


//HC-SR04 Sensor connection
  const int trigPin = 11;
  const int echoPin = 12;   

  long duration;
  int distance;

  int left_sensor_state;
  int right_sensor_state;

void setup() {
  pinMode(MotorKananMundur,OUTPUT);
  pinMode(MotorKananMaju,OUTPUT); //mo ka maju
  pinMode(MotorKiriMundur,OUTPUT);
  pinMode(MotorKiriMaju,OUTPUT); //mo ki maju
  
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  //begin serial communication
  Serial.begin(9600);
  delay(2000);
  
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

  
  //sensor jarak
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);

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

  
 if(distance < stop_distance)
 {

  mundur();
  delay(250);
  berhenti();
  delay(500);
  kiri();
  delay(1000);
  maju();
  delay(400);
  kanan();
  delay(600);
  maju();
  delay(500);
  kanan();
  delay(500);
  maju();
  delay(800);
  
//Serial.println(analogRead(lefts));
//        Serial.println(analogRead(rights));
//  //right_sensor_state == 1023;
//       if(!analogRead(rights)<=300){
//        
//        left_sensor_state = analogRead(lefts);
//        right_sensor_state = analogRead(rights);
//       mundur();
//        delay(100);
//        kiri();
//        delay (800);
//  
//        }
        
 
}
  

 
  
}


