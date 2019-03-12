// IR Sensors
int sensor1 = 6;      // Left most sensor
int sensor2 = 7;
int sensor3 = 8;
int sensor4 = 9;      // Right most sensor

// Initial Values of Sensors
int sensor[4] = {0, 0, 0, 0};

// Motor Variables
int ENA = 10; //kiri
int LeftMotorForward  = 2; //maju kiri
int LeftMotorBackward = 3; //mundur kiri
int RightMotorForward = 4; //maju kanan
int RightMotorBackward = 5; //mundur kanan
int ENB = 11; //kanan

//Initial Speed of Motor
int initial_motor_speed = 140; //standar 140

// Output Pins for Led
int ledPin1 = A3;
int ledPin2 = A4;

// PID Constants
float Kp = 25; //std 25
float Ki = 0;  //std 0
float Kd = 17; //std 15

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int flag = 0;

void setup()
{
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);

  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(LeftMotorForward , OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);

  Serial.begin(9600);                     //setting serial monitor at a default baund rate of 9600
  delay(500);
  Serial.println("Started !!");
  delay(1000);
}
void loop()
{
  read_sensor_values();
  Serial.print(error);
  if (error == 100) {               // Make left turn untill it detects straight path
    Serial.print("\t");
    Serial.println("Left");
    do {
      read_sensor_values();
      analogWrite(ENA, 110); //Left Motor Speed
      analogWrite(ENB, 90); //Right Motor Speed
      sharpLeftTurn();
    } while (error != 0);

  } else if (error == 101) {          // Make right turn in case of it detects only right path (it will go into forward direction in case of staright and right "|--")
                                      // untill it detects straight path.
    Serial.print("\t");
    Serial.println("Right");
    analogWrite(ENA, 110); //Left Motor Speed
    analogWrite(ENB, 90); //Right Motor Speed
    forward();
    delay(200);
    stop_bot();
    read_sensor_values();
    if (error == 102) {
      do {
        analogWrite(ENA, 110); //Left Motor Speed
        analogWrite(ENB, 90); //Right Motor Speed
        sharpRightTurn();
        read_sensor_values();
      } while (error != 0);
    }
  } else if (error == 102) {        // Make left turn untill it detects straight path
    Serial.print("\t");
    Serial.println("Sharp Left Turn");
    do {
      analogWrite(ENA, 110); //Left Motor Speed
      analogWrite(ENB, 90); //Right Motor Speed
      sharpLeftTurn();
      read_sensor_values();
      if (error == 0) {
        stop_bot();
        delay(200);
      }
    } while (error != 0);
  } else if (error == 103) {        // Make left turn untill it detects straight path or stop if dead end reached.
    if (flag == 0) {
      analogWrite(ENA, 110); //Left Motor Speed
      analogWrite(ENB, 90); //Right Motor Speed
      forward();
      delay(200);
      stop_bot();
      read_sensor_values();
      if (error == 103) {     /**** Dead End Reached, Stop! ****/
        stop_bot();
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        flag = 1;
      } else {        /**** Move Left ****/
        analogWrite(ENA, 110); //Left Motor Speed
        analogWrite(ENB, 90); //Right Motor Speed
        sharpLeftTurn();
        delay(200);
        do {
          Serial.print("\t");
          Serial.println("Left Here");
          read_sensor_values();
          analogWrite(ENA, 110); //Left Motor Speed
          analogWrite(ENB, 90); //Right Motor Speed
          sharpLeftTurn();
        } while (error != 0);
      }
    }
  } else {
    calculate_pid();
    motor_control();
  }
}

void read_sensor_values()
{
  sensor[0] = !digitalRead(sensor1);
  sensor[1] = !digitalRead(sensor2);
  sensor[2] = !digitalRead(sensor3);
  sensor[3] = !digitalRead(sensor4);

  /*
    Serial.print(sensor[0]);
    Serial.print("\t");
    Serial.print(sensor[1]);
    Serial.print("\t");
    Serial.print(sensor[2]);
    Serial.print("\t");
    Serial.println(sensor[3]);*/

  if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1))
    error = 3;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1))
    error = 2;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1))
    error = 1;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1))
    error = 0;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 1))
    error = -1;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0))
    error = -2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0))
    error = -3;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1)) // Turn robot left side
    error = 100;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0)) // Turn robot right side
    error = 101;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0)) // Make U turn
    error = 102;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0)) // Turn left side or stop
    error = 103;
}

void calculate_pid()
{
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control()
{
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed - PID_value;
  int right_motor_speed = initial_motor_speed + PID_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

  /*Serial.print(PID_value);
    Serial.print("\t");
    Serial.print(left_motor_speed);
    Serial.print("\t");
    Serial.println(right_motor_speed);*/

  analogWrite(ENA, left_motor_speed); //Left Motor Speed
  analogWrite(ENB, right_motor_speed - 30); //Right Motor Speed

  //following lines of code are to make the bot move forward
  forward();
}

void forward()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward , HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
}
void reverse()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(LeftMotorForward , LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
}
void right()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward , HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
}
void left()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward , LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
}
void sharpRightTurn() {
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward , HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
}
void sharpLeftTurn() {
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(LeftMotorForward , LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
}
void stop_bot()
{
  /*The pin numbers and high, low values might be different depending on your connections */
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(LeftMotorForward , LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
}
