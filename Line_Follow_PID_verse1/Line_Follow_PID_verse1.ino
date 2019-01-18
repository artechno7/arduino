float pTerm, iTerm, dTerm;
int error;
int previousError;
float kp = 11; //11
float ki = 0;
float kd = 11; //11
float output;
int integral, derivative;
int irSensors[] = {8, 7, 6}; //IR sensor pins
int irReadings[3];
int motor1Forward = 5;
int motor1Backward = 4;
int motor1pwmPin = 10;
int motor2Forward = 3;
int motor2Backward = 2;
int motor2pwmPin = 9;
int motor1newSpeed;
int motor2newSpeed;
int motor2Speed = 120; //Default 70
int motor1Speed = 150; //Default 120

void setup() {
  //Declare all IR sensors as inputs
  for (int pin = 0; pin < 3; pin++) {
    int pinNum = irSensors[pin];
    pinMode(pinNum, INPUT);
  }
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Backward, OUTPUT);
  pinMode(motor1pwmPin, OUTPUT);
  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Backward, OUTPUT);
  pinMode(motor2pwmPin, OUTPUT);
}

void loop() {
  //Put all of our functions here
  readIRSensors();
  calculateError();
  pidCalculations();
  changeMotorSpeed();
}

void readIRSensors() {
  //Read the IR sensors and put the readings in irReadings array
  for (int pin = 0; pin < 3; pin++) {
    int pinNum = irSensors[pin];
    irReadings[pin] = digitalRead(pinNum);
  }
}

void calculateError() {
  //Determine an error based on the readings
  if ((irReadings[0] == 1) && (irReadings[1] == 1) && (irReadings[2] == 0)) {
    error = 2;
  } else if ((irReadings[0] == 1) && (irReadings[1] == 0) && (irReadings[2] == 0)) {
    error = 1;
  } else if ((irReadings[0] == 1) && (irReadings[1] == 0) && (irReadings[2] == 1)) {
    error = 0;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 1)) {
    error = -1;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 1) && (irReadings[2] == 1)) {
    error = -2;
  } else if ((irReadings[0] == 1) && (irReadings[1] == 1) && (irReadings[2] == 1)) {
    if (previousError == -2) {
      error = -3;
    } else {
      error = 3;
    }
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0)) {
    error = 0;
  }
}

void pidCalculations() {
  pTerm = kp * error;
  integral += error;
  iTerm = ki * integral;
  derivative = error - previousError;
  dTerm = kd * derivative;
  output = pTerm + iTerm + dTerm;
  previousError = error;
}

void changeMotorSpeed() {
  //Change motor speed of both motors accordingly
  motor2newSpeed = motor2Speed + output;
  motor1newSpeed = motor1Speed - output;
  //Constrain the new speed of motors to be between the range 0-255
  constrain(motor2newSpeed, 0, 255);
  constrain(motor1newSpeed, 0, 255);
  //Set new speed, and run motors in forward direction
  analogWrite(motor2pwmPin, motor2newSpeed);
  analogWrite(motor1pwmPin, motor1newSpeed);
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor1Backward, LOW);
}
