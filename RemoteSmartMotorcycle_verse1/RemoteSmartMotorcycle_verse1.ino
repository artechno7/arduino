//rOBOT REMOTE BLUETOOTH 05

//#include <SoftwareSerial.h> //wajib pake kalau pin bluetooth tidak di 0 dan 1

//PIN BLUETOOTH RX,TX,0,1
//control pins
const int pinkontak = 13;
const int pinstarter = 12;
const int pinkiri = 11;
const int pinkanan = 10;
const int pinklakson = 9;


char val;
void setup() {
  
  // Control Pins as Output
  pinMode(pinkontak, OUTPUT);
  pinMode(pinstarter, OUTPUT);
  pinMode(pinklakson, OUTPUT);
  pinMode(pinkiri, OUTPUT);
  pinMode(pinkanan, OUTPUT);
  
  
  
  
  Serial.begin(9600);
}

void kontakon()
{
 digitalWrite(pinkontak, HIGH);
}

void kontakoff()
{
 digitalWrite(pinkontak, LOW);
}

void klaksonon()
{
 digitalWrite(pinklakson, HIGH);
}

void klaksonoff()
{
 digitalWrite(pinklakson, LOW);
}
void starteron()
{
 digitalWrite(pinstarter, HIGH);
}

void starteroff()
{
 digitalWrite(pinstarter, LOW);
}

void kirion()
{
 digitalWrite(pinkiri, HIGH);
// delay(300);
// digitalWrite(pinkiri, LOW);
// delay(300);
}

void kirioff()
{
 digitalWrite(pinkiri, LOW);
}

void kananon()
{
 digitalWrite(pinkanan, HIGH);
// delay(300);
// digitalWrite(pinkanan, LOW);
// delay(300);
 
}

void kananoff()
{
 digitalWrite(pinkanan, LOW);
}

void hazardon()
{
 digitalWrite(pinkiri, HIGH);
 digitalWrite(pinkanan, HIGH);
// delay(300);
// digitalWrite(pinkiri, LOW);
// digitalWrite(pinkanan, LOW);
// delay(300);
}

void hazardoff()
{
 digitalWrite(pinkiri, LOW);
 digitalWrite(pinkanan, LOW);
}


void loop() {
if( Serial.available() >0 ) {
    val = Serial.read();
    Serial.println(val); 
}
  if( val == '1' ) {
    kontakon(); }
  else if( val == '2' ) {
    klaksonon(); }
  else if( val == '3' ) {
    kirion(); }
  else if( val == '4' ) {
    kananon(); }
  else if( val == '5' ) {
    hazardon(); } 
  else if( val == '6' ) {
    starteron(); }
  
  else if( val == 'A' ) {
    kontakoff(); }
  else if( val == 'B' ) {
    klaksonoff(); }
  else if( val == 'C' ) {
    kirioff(); }
  else if( val == 'D' ) {
    kananoff(); }
  else if( val == 'E' ) {
    hazardoff(); }
  else if( val == 'F' ) {
    starteroff(); }
}
