int sensorPin = A0;    
  
int ledPin1 = 2; 
int ledPin2 = 3; 
int ledPin3 = 4;  
int sensorValue = 0;  

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1,INPUT);
  pinMode(ledPin2,INPUT);
  pinMode(ledPin3,INPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  
  if(sensorValue<100){
    digitalWrite(ledPin1,1);
    digitalWrite(ledPin2,0);
    digitalWrite(ledPin3,0);
//    delay(100);
//    digitalWrite(ledPin1,0);
//    digitalWrite(ledPin2,0);
//    digitalWrite(ledPin3,0);
//    delay(100);
  }
  else if(sensorValue<300){
    digitalWrite(ledPin2,1);
    digitalWrite(ledPin1,0);
    digitalWrite(ledPin3,0);
  }
  else if(sensorValue<600){
    digitalWrite(ledPin3,1);
    digitalWrite(ledPin1,0);
    digitalWrite(ledPin2,0);
  }
  else{
    digitalWrite(ledPin1,0);
    digitalWrite(ledPin2,0);
    digitalWrite(ledPin3,0);
  }
}
