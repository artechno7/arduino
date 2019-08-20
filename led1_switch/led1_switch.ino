int tombol= 2;
int led= 12;
int nilai;
void setup(){
pinMode(led, OUTPUT);
pinMode(tombol, INPUT);
}
void loop(){
nilai= digitalRead(tombol);
if(nilai == 1){
digitalWrite(led, HIGH);
}
else{
digitalWrite(led, LOW);
}
}
