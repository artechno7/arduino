#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

// L298N Control Pins
const int MotorKiriMaju = 2;
const int MotorKiriMundur = 3;
const int MotorKananMaju = 4;
const int MotorKananMundur = 5;

const int LeftMotorForward = MotorKiriMaju;
const int LeftMotorBackward =  MotorKiriMundur;
const int RightMotorForward = MotorKananMaju;
const int RightMotorBackward = MotorKananMundur;


// Line Sensor Pins
  const int lefts = 6; 
  const int rights = 7; 

int left_sensor_state;
int right_sensor_state;

//sensor pin avoider
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name

//mobil remote
const int e=13, f=8, g=7; //   e = bel, f,g  = flash & bel
char val;

//button
const int buttonA = 11;
const int buttonB = 12;  
int buttonStateA = 0;
int buttonStateB = 0;

void setup() {
  pinMode(MotorKananMundur,OUTPUT);
  pinMode(MotorKananMaju,OUTPUT); 
  pinMode(MotorKiriMundur,OUTPUT);
  pinMode(MotorKiriMaju,OUTPUT); 
  
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);

  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  
  //servo function
  servo_motor.attach(10); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);


  //begin serial communication
  Serial.begin(9600);
  //delay(3000); //lama jalan waktu arduino nyalan
  
}

void maju()
{
  Serial.println("going forward");
  digitalWrite(MotorKiriMaju,HIGH);
  digitalWrite(MotorKananMaju,HIGH);
  digitalWrite(MotorKananMundur,LOW);
  digitalWrite(MotorKiriMundur,LOW);
 
}

void mundur()
{
  digitalWrite(MotorKiriMundur,HIGH);
  digitalWrite(MotorKananMundur,HIGH);
  digitalWrite(MotorKiriMaju,LOW);
  digitalWrite(MotorKananMaju,LOW);
}

void kanan()
{
  Serial.println("turning right");
  digitalWrite(MotorKiriMaju,HIGH);
  digitalWrite(MotorKananMundur,HIGH);
  digitalWrite(MotorKananMaju,LOW);
  digitalWrite(MotorKiriMundur,LOW);

}

void kiri()
{
  Serial.println("turning left");
  digitalWrite(MotorKananMaju,HIGH);
  digitalWrite(MotorKiriMundur,HIGH);
  digitalWrite(MotorKiriMaju,LOW);
  digitalWrite(MotorKananMundur,LOW);
}

void berhenti()
{
  Serial.println("stop");
  digitalWrite(MotorKananMaju,LOW);
  digitalWrite(MotorKiriMundur,LOW);
  digitalWrite(MotorKiriMaju,LOW);
  digitalWrite(MotorKananMundur,LOW);
}

void flskiri()
{
 digitalWrite(f,HIGH);delay(300);
 digitalWrite(f,LOW); 
}

void flskanan()
{
 digitalWrite(g,HIGH);delay(300);
 digitalWrite(g,LOW); 
}

void bel()
{
 digitalWrite(e,HIGH);delay(300);
 digitalWrite(e,LOW); 
}

void off()
{
    digitalWrite(RightMotorForward,LOW);
    digitalWrite(RightMotorBackward,LOW);
    digitalWrite(LeftMotorForward,LOW);
    digitalWrite(LeftMotorBackward,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
       
}


//ROBOT LINE FOLLOWER --
void linefollower(){
left_sensor_state = digitalRead(lefts);
right_sensor_state = digitalRead(rights);

  

  //line detected by both
  if(right_sensor_state == LOW && left_sensor_state == LOW){
   
    maju();
  }
  
  //line detected by right sensor
  if(right_sensor_state == HIGH && left_sensor_state == LOW){
  
    kanan();
  }

  //line detected by left sensor
  if(right_sensor_state == LOW && left_sensor_state == HIGH){
    
    kiri();
  }

  //line detected by none
  if(right_sensor_state == HIGH && left_sensor_state == HIGH){
    //stop
    berhenti();
  }
}

//avoider
int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveBackward(){

  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRight(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
 
  
  
}

void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void avoider(){



  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 27){ //jarak
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}



void mobilremote() {
if( Serial.available() >0 ) {
    val = Serial.read();
    Serial.println(val); 
}
//if( BTSerial.available() >0 ) {
 //   val = BTSerial.readString();
//    Serial.println(val); 
//}

  if( val == '1' ) {
    maju(); }
  else if( val == '2' ) {
    kiri(); }
  else if( val == '3' ) {
    mundur(); }
  else if( val == '4' ) {
    kanan(); }
  else if( val == '5' ) {
    bel(); } 
  else if( val == '6' ) {
    flskiri(); }
  else if( val == '7' ) {
    flskanan();  
 }
  else if( val == 'A' ) {
    off(); 
    }
  else if( val == 'B' ) {
    off();    
    }
  else if( val == 'C' ) {
    off(); }
  else if( val == 'D' ) {
    off(); }
  else if( val == 'E' ) {
    off(); }
  else if( val == 'F' ) {
    off(); }
  else if( val == 'G' ) {
    off();    
  }
}


void loop() {
  // read the state of the pushbutton value:
  buttonStateA = digitalRead(buttonA);
  buttonStateB = digitalRead(buttonB);
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateA == HIGH && buttonStateB == LOW)  {
      avoider();
  } 
  else if (buttonStateA == LOW && buttonStateB == HIGH)   {
    linefollower();
  }
  else if (buttonStateA == HIGH && buttonStateB == HIGH)   {
    mobilremote();
  }
  else if (buttonStateA == LOW && buttonStateB == LOW)   {
    off();
  }
}
