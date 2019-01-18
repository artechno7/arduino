
#define lefts A4 
#define rights A5 

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT); 
  
  pinMode(lefts,INPUT);
  pinMode(rights,INPUT);
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
  //line detected by both
  if(analogRead(lefts)<=400 && analogRead(rights)<=400){
    //stop
    berhenti();
  }
  //line detected by left sensor
  else if(analogRead(lefts)<=400 && !analogRead(rights)<=400){
    //turn left
    kiri();
    /*
    motor1.run(RELEASE);
    motor2.run(FORWARD);
     */
  }
  //line detected by right sensor
  else if(!analogRead(lefts)<=400 && analogRead(rights)<=400){
    //turn right
    kanan();
    /*
    motor1.run(FORWARD);
    motor2.run(RELEASE);
     */
  }
  //line detected by none
  else if(!analogRead(lefts)<=400 && !analogRead(rights)<=400){
    //stop
    maju();
    /*
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
     */
  }
  
}


