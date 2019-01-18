#include <CurieBLE.h>
BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming) /device bluetootnya
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service alamat service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
// BLE LED Switch Characteristic - 128ID UUID pilihan/kustom, dibaca dan ditulis oleh pusat
BLEUnsignedCharCharacteristic switchCharacteristic1("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic switchCharacteristic2("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic switchCharacteristic3("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic switchCharacteristic4("19B10004-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic switchCharacteristic5("19B10005-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic switchCharacteristic6("19B10006-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEUnsignedCharCharacteristic switchCharacteristic7("19B10007-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);


const int ledPin1=13, ledPin2=12, ledPin3=11, ledPin4=10, ledPin5=9, ledPin6=8;

void setup() {
  Serial.begin(9600);
  // set LED pin to output mode - set device sbg OUTPUT
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);

  // begin initialization Permulaan Inisial Bluetooth
  BLE.begin();
  // set advertised local name and service UUID: setel nama lokal dan layanan UUID yang diaktifkan/dideklarasikan /nama bluetooth
  BLE.setLocalName("FATONI");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service  tambahkan characteristik untuk layanan / switch pilihan
  ledService.addCharacteristic(switchCharacteristic1);
  ledService.addCharacteristic(switchCharacteristic2);
  ledService.addCharacteristic(switchCharacteristic3);
  ledService.addCharacteristic(switchCharacteristic4);
  ledService.addCharacteristic(switchCharacteristic5);
  ledService.addCharacteristic(switchCharacteristic6);
  ledService.addCharacteristic(switchCharacteristic7);
  BLE.addService(ledService);

  // set the initial value for the characeristic: seting nilai inisial untuk switch/pilihan awal 0
  switchCharacteristic1.setValue(0);
  switchCharacteristic2.setValue(0);
  switchCharacteristic3.setValue(0);
  switchCharacteristic4.setValue(0);
  switchCharacteristic5.setValue(0);
  switchCharacteristic6.setValue(0);
  switchCharacteristic7.setValue(0);
  BLE.advertise(); 
  //Serial.println("BLE LED Peripheral");
  }

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    // while the central is still connected to peripheral:
    while (central.connected()) 
    {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic1.written()) {
        if (switchCharacteristic1.value()==49) {   // any value other than 0
          digitalWrite(ledPin1, HIGH);         // will turn the LED on
          }
          else {                              // a 0 value
          //Serial.println(F("LED off"));
          digitalWrite(ledPin1, LOW);          // will turn the LED off
          }
      }
 
   if (switchCharacteristic2.written()) 
      {
      if (switchCharacteristic2.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(ledPin2, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(ledPin2, LOW); //led mati
          }
      }

     
      if (switchCharacteristic3.written()) 
      {
      if (switchCharacteristic3.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(ledPin3, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(ledPin3, LOW); //led mati
          }
      }
      
      if (switchCharacteristic4.written()) 
      {
      if (switchCharacteristic4.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(ledPin4, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(ledPin4, LOW); //led mati
          }
      }

      if (switchCharacteristic5.written()) 
      {
      if (switchCharacteristic5.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(ledPin5, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(ledPin5, LOW); //led mati
          }
      }

      if (switchCharacteristic6.written()) 
      {
      if (switchCharacteristic6.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(ledPin6, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(ledPin6, LOW); //led mati
          }
      }

      if (switchCharacteristic7.written()) 
      {
      if (switchCharacteristic7.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin3, HIGH);
          digitalWrite(ledPin4, HIGH);
          digitalWrite(ledPin5, HIGH);
          digitalWrite(ledPin6, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(ledPin1, LOW); //led mati
          digitalWrite(ledPin2, LOW);
          digitalWrite(ledPin3, LOW);
          digitalWrite(ledPin4, LOW);
          digitalWrite(ledPin5, LOW);
          digitalWrite(ledPin6, LOW);
          }
      }

     
      
    }
  }
 }
    
 
