int button= 10;
int nilaitombol;
int count;
int led= 2;

void setup(){
pinMode(button, INPUT);
pinMode(led, OUTPUT);
}

void loop(){
nilaitombol= digitalRead(button);

if(nilaitombol == 1){
  count++;
  delay(300);
if(count==1){
  digitalWrite(led, HIGH);
  }
if(count==2){
  digitalWrite(led, LOW);
  count=0;
  }
}
}
