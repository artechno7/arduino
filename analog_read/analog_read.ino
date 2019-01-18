void setup() {
Serial.begin(9600); //digunakan untuk komunikasi Arduino dengan Serial Monitot (komputer)
}
void loop() {
int sensorValue = analogRead(A0); //digunakan untuk membaca nilai pada pin A0
float voltage = sensorValue * (5.0 / 1023.0); //mengubah nilai dari sensorValue menjadi Voltage
Serial.println(voltage); //menampilkan nilai voltage di Serial Monitor 
delay(500);
}
