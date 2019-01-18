//ROBOT LINE FOLLOWER --

// L298N Control Pins
const int MotorKiriMaju = 5;
const int MotorKiriMundur = 4;
const int MotorKananMaju = 3;
const int MotorKananMundur = 2;

// Line Sensor Pins
  const int lefts = 6; 
  const int rights = 7; 

int left_sensor_state;
int right_sensor_state;
  
void setup() {
  pinMode(MotorKananMundur,OUTPUT);
  pinMode(MotorKananMaju,OUTPUT); 
  pinMode(MotorKiriMundur,OUTPUT);
  pinMode(MotorKiriMaju,OUTPUT); 
  
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);

  //begin serial communication
  Serial.begin(9600);
  delay(3000);
  
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

void loop(){
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
