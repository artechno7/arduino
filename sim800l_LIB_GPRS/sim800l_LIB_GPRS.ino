#include <gprs.h>
#include <SoftwareSerial.h>

GPRS gprs;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("SIM800L Demo Send SMS via Seeeduino");
  gprs.preInit();
  delay(1000);
  while(0 != gprs.init()) {
      delay(1000);
      Serial.print("init error\r\n"); //pesan di Serial Monitor jika proses init module GPRS Gagal
  }  
  Serial.println("Init succes..."); //pesan di Serial Monitor jika proses init module GPRS Sukses
  delay(1000);
  
  //Format Coding Kirim SMS
  gprs.sendSMS("085780391803","Test Send SMS with Seeeduino Lib"); //define phone number and text
}

void loop() {
  //nothing to do
}
