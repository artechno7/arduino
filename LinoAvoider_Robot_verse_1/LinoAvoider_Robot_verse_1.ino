
#define lefts A4 
#define rights A5 
#define avoids A4

int left_sensor_state;
int right_sensor_state;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT); 
  
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
  pinMode(avoids,INPUT);
  //begin serial communication
  Serial.begin(9600);
  
}

void maju()
{
  digitalWrite(5,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
}

void mundur()
{
  digitalWrite(4,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(3,LOW);
}

void kanan()
{
  digitalWrite(5,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
}

void kiri()
{
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(2,LOW);
}

void berhenti()
{
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(2,LOW);
}

void loop(){
  //printing values of the sensors to the serial monitor
  Serial.println(analogRead(lefts));
  Serial.println(analogRead(rights));
  
  //ovoider
  if(analogRead(avoids)<=300)
 {
  //mundur
  mundur();
  delay(250);
  
  //kiri

  kiri();
  delay(900);

  //maju
  maju();
  delay(800);

  //kanan
  kanan();
  delay(900);

  //maju
  maju();
  delay(700);

  //kanan
   kanan();
  delay(650);

  //maju
  maju();

  //left_sensor_state == 600;

  while(!analogRead(lefts)<=300){

  //left_sensor_state = digitalRead(lefts);
  //right_sensor_state = digitalRead(rights);
  Serial.println("in the first while");
  
 
}
  //mundur
  mundur();
  delay(100);

  //kiri
  kiri();
  delay (500);

  }
  
  
  //line detected by both
  if(analogRead(lefts)<=300 && analogRead(rights)<=300){
    //stop
    maju();
  }
  //line detected by left sensor
  else if(analogRead(lefts)<=300 && !analogRead(rights)<=300){
    //turn left
    kanan();
    /*
    motor1.run(RELEASE);
    motor2.run(FORWARD);
     */
  }
  //line detected by right sensor
  else if(!analogRead(lefts)<=300 && analogRead(rights)<=300){
    //turn right
    kiri();
    /*
    motor1.run(FORWARD);
    motor2.run(RELEASE);
     */
  }
  //line detected by none
  else if(!analogRead(lefts)<=300 && !analogRead(rights)<=300){
    //stop
    berhenti();
    /*
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
     */
  }

  
  
}


