int trig= 11; // membuat varibel trig yang di set ke-pin 3
int echo= 12; // membuat variabel echo yang di set ke-pin 2
int led1= 2;
int led2= 3;
int led3= 4;
long durasi, jarak; // membuat variabel durasi dan jarak
void setup() {
pinMode(trig, OUTPUT); // set pin trig menjadi OUTPUT
pinMode(echo, INPUT); // set pin echo menjadi INPUT
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
Serial.begin(9600); // digunakan untuk komunikasi Serial dengan komputer
}
void loop() {
// program dibawah ini agar trigger memancarakan suara ultrasonic
digitalWrite(trig, LOW);
delayMicroseconds(8);
digitalWrite(trig, HIGH);
delayMicroseconds(8);
digitalWrite(trig, LOW);
delayMicroseconds(8);
durasi= pulseIn(echo, HIGH); // menerima suara ultrasonic
jarak= (durasi/2) / 29.1; // mengubah durasi menjadi jarak (cm)
Serial.println(jarak); // menampilkan jarak pada Serial Monitor
 if (jarak > 75) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
 }
 if ((jarak > 51) && (jarak <=75)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
 }
  if ((jarak > 11) && (jarak <=50)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
 }
  if ((jarak > 0) && (jarak <=10)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
 }
}
