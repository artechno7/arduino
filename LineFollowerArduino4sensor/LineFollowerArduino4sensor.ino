// ------ Project Membuat Robot Line Follower 4 Sensor ------- //
// ------------- Dibuat oleh : M. Nofgi Y.P.U. -------------- //
// ------------- www.nofgipiston.wordpress.com -------------- //


// inialisasi pin motor kanan dan motor kiri
// motor1 dan motor2 = motor kanan
// motor3 dan motor4 = motor kiri
const int motor1 = 7;
const int motor2 = 6;
const int motor3 = 5;
const int motor4 = 4;


// inialisasi pi sensor garis 1 sampai 4
// sensor1 dan snsor2 = sensor sebelah kanan
// sensor3 dan sensor4 = sensor sebelah kiri
const int sensor1 = A5;
const int sensor2 = A4;
const int sensor3 = A3;
const int sensor4 = A2;

// inialisasi pin speed motor
// wajib pin support PWM
const int pinSpeed = 9;

// inialisasi variabel data 1 sampai 4
int data1, data2, data3, data4;

// inialisasi nilai kecepatan motor
// range nilai antara 0 sampai 255
int speedMotor = 255;

// ---------- program dfault/setting awal ---------- //

void setup()
{
 // inialisasi pin motor sebagai output
 pinMode(motor1, OUTPUT);
 pinMode(motor2, OUTPUT);
 pinMode(motor3, OUTPUT);
 pinMode(motor4, OUTPUT);

// inialisasi pin sensor sebagai input
 pinMode(sensor1, INPUT);
 pinMode(sensor2, INPUT);
 pinMode(sensor3, INPUT);
 pinMode(sensor4, INPUT);

// inialisasi pin speed motor sebagai output
 pinMode(pinSpeed, OUTPUT);
}

// ---------- program utama, looping/berulang terus-menerus ---------- //

void loop ()
{
 // masing2 variabel data menyimpan hasil pembacaan sensor
 // berupa logic LOW/HIGH
 data1 = digitalRead(sensor1);
 data2 = digitalRead(sensor2);
 data3 = digitalRead(sensor3);
 data4 = digitalRead(sensor4);

// mengatur kecepatan motor
 analogWrite(pinSpeed, speedMotor);

// ----------- pengaturan jalannya robot sesuai pembacaan sensor ------------ //

if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == LOW)
 {
 //maju
 digitalWrite(motor1, HIGH);
 digitalWrite(motor2, LOW);
 digitalWrite(motor3, HIGH);
 digitalWrite(motor4, LOW);
 }

else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW)
 {
 //kanan
 digitalWrite(motor1, LOW);
 digitalWrite(motor2, HIGH);
 digitalWrite(motor3, HIGH);
 digitalWrite(motor4, LOW);
 }

else if (data1 == LOW && data2 == HIGH && data3 == HIGH && data4 == HIGH)
 {
 //kiri
 digitalWrite(motor1, HIGH);
 digitalWrite(motor2, LOW);
 digitalWrite(motor3, LOW);
 digitalWrite(motor4, HIGH);
 }

else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == LOW)
 {
 //kanan
 digitalWrite(motor1, LOW);
 digitalWrite(motor2, HIGH);
 digitalWrite(motor3, HIGH);
 digitalWrite(motor4, LOW);
 }

else if (data1 == LOW && data2 == LOW && data3 == HIGH && data4 == HIGH)
 {
 //kiri
 digitalWrite(motor1, HIGH);
 digitalWrite(motor2, LOW);
 digitalWrite(motor3, LOW);
 digitalWrite(motor4, HIGH);
 }

else if (data1 == HIGH && data2 == LOW && data3 == LOW && data4 == LOW)
 {
 //kanan
 digitalWrite(motor1, LOW);
 digitalWrite(motor2, HIGH);
 digitalWrite(motor3, HIGH);
 digitalWrite(motor4, LOW);
 }

else if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == HIGH)
 {
 //kiri
 digitalWrite(motor1, HIGH);
 digitalWrite(motor2, LOW);
 digitalWrite(motor3, LOW);
 digitalWrite(motor4, HIGH);
 }

else if (data1 == HIGH && data2 == LOW && data3 == HIGH && data4 == LOW)
 {
 //kanan
 digitalWrite(motor1, LOW);
 digitalWrite(motor2, HIGH);
 digitalWrite(motor3, HIGH);
 digitalWrite(motor4, LOW);
 }

else if (data1 == LOW && data2 == HIGH && data3 == LOW && data4 == HIGH)
 {
 //kiri
 digitalWrite(motor1, HIGH);
 digitalWrite(motor2, LOW);
 digitalWrite(motor3, LOW);
 digitalWrite(motor4, HIGH);
 }

else if (data1 == LOW && data2 == HIGH && data3 == LOW && data4 == LOW)
 {
 //kanan
 digitalWrite(motor1, LOW);
 digitalWrite(motor2, HIGH);
 digitalWrite(motor3, HIGH);
 digitalWrite(motor4, LOW);
 }

else if (data1 == LOW && data2 == LOW && data3 == HIGH && data4 == LOW)
 {
 //kiri
 digitalWrite(motor1, HIGH);
 digitalWrite(motor2, LOW);
 digitalWrite(motor3, LOW);
 digitalWrite(motor4, HIGH);
 }

else if (data1 == LOW && data2 == HIGH && data3 == HIGH && data4 == LOW)
 {
 //maju
 digitalWrite(motor1, HIGH);
 digitalWrite(motor2, LOW);
 digitalWrite(motor3, HIGH);
 digitalWrite(motor4, LOW);
 }

else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH)
 {
 //maju
 digitalWrite(motor1, HIGH);
 digitalWrite(motor2, LOW);
 digitalWrite(motor3, HIGH);
 digitalWrite(motor4, LOW);
 }
}
