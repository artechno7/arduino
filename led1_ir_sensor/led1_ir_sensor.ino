/* Test deteksi sinar infrared
 sensor infrared di hubungkan ke PIN A0 (Analog)
 apabila sensor infrared mendapat sinar inframerah
 maka, LED 13 nyala, jika tidak LED 13 padam
 sementara itu nilai yang diterima sensor inframerah
 dapat dipantau melalui serial monitor
 oleh : Aan Darmawan
 blog : http://valfa.blogspot.com
 */
void setup() {                
  Serial.begin(9600); 
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);   
}
int sensor;
void loop() {
  // baca nilai sensor di PIN A0 (Analog) dan kirim ke serial
  sensor=analogRead(A0);
  Serial.print("Nilai: ");  
  Serial.println(sensor);  
  // Jika sensor mendapat sinar infra merah nilai sensor turun
  // Angka 900 dapat diubah sesuai jarak pantul yang diinginkan
  // dan nilai hasil pemantauan di serial monitor
  if(sensor<=100) 
    digitalWrite(13, HIGH);   // LED 13 dinyalakan
  else               
    digitalWrite(13, LOW);    // LED 13 dipadamkan
  delay(500);              // delay 0,5 detik
}
