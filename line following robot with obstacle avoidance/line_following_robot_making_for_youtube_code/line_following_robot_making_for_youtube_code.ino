
/*
 * Created by ASHIQ SHIBU (MAKER Q)
 * Project: Line following robot with obstacle avoidance
 * https://www.youtube.com/watch?v=Py2lBehF9rA
 */
  int vSpeed = 110;                      
  int turn_speed = 230;       // 0 - 255  max
  int t_p_speed = 125;
  int stop_distance = 12;
  int turn_delay = 10;


//HC-SR04 Sensor connection
  const int trigPin = 11;
  const int echoPin = 12;

//L293 Connection   
  const int motorA1      = 3;  
  const int motorA2      = 4; 
  const int motorAspeed  = 5;
  const int motorB1      = 7; 
  const int motorB2      = 8; 
  const int motorBspeed  =6;

//Sensor Connection
  const int left_sensor_pin =9;
  const int right_sensor_pin =10;

  
  int turnspeed;
  int left_sensor_state;
  int right_sensor_state;

  long duration;
  int distance;

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
    
  Serial.begin(9600);

  delay(3000);                              
  
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);


left_sensor_state = digitalRead(left_sensor_pin);
right_sensor_state = digitalRead(right_sensor_pin);



if(right_sensor_state == HIGH && left_sensor_state == LOW)
{
  Serial.println("turning right");

  digitalWrite (motorA1,LOW);
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB1,LOW);
  digitalWrite(motorB2,HIGH);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, turn_speed);
  
  }
if(right_sensor_state == LOW && left_sensor_state == HIGH)
{
  Serial.println("turning left");
  
  digitalWrite (motorA1,HIGH);
  digitalWrite(motorA2,LOW);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  analogWrite (motorAspeed, turn_speed);
  analogWrite (motorBspeed, vSpeed);

  delay(turn_delay);
  }

if(right_sensor_state == LOW && left_sensor_state == LOW)
{
  Serial.println("going forward");

  digitalWrite (motorA1,LOW);
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);

  delay(turn_delay);
  
  }

if(right_sensor_state == HIGH && left_sensor_state == HIGH)
{ 
  Serial.println("stop");
  
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);
  while(true){
  
 }
  }

 if(distance < stop_distance)
 {

  digitalWrite (motorA1,HIGH); //mundur
  digitalWrite(motorA2,LOW);                       
  digitalWrite (motorB1,LOW);
  digitalWrite(motorB2,HIGH);
  delay(250);
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);
  delay(500);
  digitalWrite (motorA1,HIGH); //kiri
  digitalWrite(motorA2,LOW);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  analogWrite (motorAspeed, t_p_speed);
  analogWrite (motorBspeed, t_p_speed);
  delay(900);


  digitalWrite (motorA1,LOW); //maju
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  analogWrite (motorAspeed, t_p_speed);
  analogWrite (motorBspeed, t_p_speed);
  delay(800);

  digitalWrite (motorA1,LOW); //kanan
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB1,LOW);
  digitalWrite(motorB2,HIGH);
  delay(900);

  digitalWrite (motorA1,LOW); //maju
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  delay(700);

   digitalWrite (motorA1,LOW); //kanan
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB1,LOW);
  digitalWrite(motorB2,HIGH);
  delay(650);

  digitalWrite (motorA1,LOW); //maju
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  left_sensor_state == HIGH;

  while(left_sensor_state == LOW){

  left_sensor_state = digitalRead(left_sensor_pin);
  right_sensor_state = digitalRead(right_sensor_pin);
  Serial.println("in the first while");
  
 
}

  digitalWrite (motorA1,HIGH); //mundur
  digitalWrite(motorA2,LOW);                       
  digitalWrite (motorB1,LOW);
  digitalWrite(motorB2,HIGH);
  delay(100);
  
  digitalWrite (motorA1,HIGH); //kiri
  digitalWrite(motorA2,LOW);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite(motorB2,LOW);
  delay (500);

  }
}










 
