const byte LED = 13;
const byte Button = 3;

byte ButtonState;
byte lastState = LOW;
byte count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT);
}

void loop() {
  ButtonState = digitalRead(Button);

  if(ButtonState && ButtonState != lastState)  // button latch, no debounce needed.
  {
    if(count < 255) // This will check to see if the count is within a range of 0 - 255, and anything over that, it will reset count back to 0. Of course, this will happen anyways because count is a BYTE, and not an int or any other type.
      count += 5; // same as count = count + 5;
    else
      count = 0;
      
    analogWrite(LED, count);
    Serial.println(count);
  } 
  lastState = ButtonState;
}

