

//motor Speed
int HighSpeed = 140; //max 255 std HML 110 90 70 HS 160 100 80
int MidSpeed = 110;
int LowSpeed = 110;
int SpeedDelay = 10;
int stop_distance = 8;



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

// Line Sensor Pins
  const int lefts = 6; 
  const int rights = 7; 
  
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
  delay(3000);
  
}

void maju()
{
  Serial.println("going forward");
  digitalWrite(MotorKiriMaju,HIGH);
  digitalWrite(MotorKananMaju,HIGH);
  digitalWrite(MotorKananMundur,LOW);
  digitalWrite(MotorKiriMundur,LOW);
  analogWrite (SpeedKiri, HighSpeed);
  analogWrite (SpeedKanan, HighSpeed);
  delay(SpeedDelay);
}

void majutd() //tanpa delay
{
  Serial.println("going forward");
  digitalWrite(MotorKiriMaju,HIGH);
  digitalWrite(MotorKananMaju,HIGH);
  digitalWrite(MotorKananMundur,LOW);
  digitalWrite(MotorKiriMundur,LOW);
  analogWrite (SpeedKiri, HighSpeed);
  analogWrite (SpeedKanan, HighSpeed);
 
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
  Serial.println("turning right");
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
  Serial.println("turning left");
  digitalWrite(MotorKananMaju,HIGH);
  digitalWrite(MotorKiriMundur,HIGH);
  digitalWrite(MotorKiriMaju,LOW);
  digitalWrite(MotorKananMundur,LOW);
  analogWrite (SpeedKiri, LowSpeed);
  analogWrite (SpeedKanan, MidSpeed);
  delay(SpeedDelay);
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
//    while(true){
//      } //berhenti total
  }

  
 if(distance < stop_distance)
 {

  mundur();
  delay(300);
  berhenti();
  delay(300);
  kiri();
  delay(300);
  maju();
  delay(600);
  kanan();
  delay(300);
  maju();
  delay(800);
  kanan();
  delay(300);
  majutd();
 
  
  left_sensor_state == HIGH;

  while(left_sensor_state == LOW){

  left_sensor_state = digitalRead(lefts);
  right_sensor_state = digitalRead(rights);
  Serial.println("in the first while");

       
  
}
        mundur();
        delay(100);
        kiri();
        delay (300);        
 
}
  

 
  
}
