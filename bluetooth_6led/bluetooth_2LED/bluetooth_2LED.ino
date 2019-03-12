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


const int kunci=13, starter=12, kiri=11, bel=10, kanan=9, lampu=8;

void setup() {
  Serial.begin(9600);
  // set LED pin to output mode - set device sbg OUTPUT
  pinMode(kunci, OUTPUT);
  pinMode(starter, OUTPUT);
  pinMode(kiri, OUTPUT);
  pinMode(bel, OUTPUT);
  pinMode(kanan, OUTPUT);
  pinMode(lampu, OUTPUT);

  // begin initialization Permulaan Inisial Bluetooth
  BLE.begin();
  // set advertised local name and service UUID: setel nama lokal dan layanan UUID yang diaktifkan/dideklarasikan /nama bluetooth
  BLE.setLocalName("SMKMUHPA");
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
          digitalWrite(kunci, HIGH);         // will turn the LED on
          }
          else {                              // a 0 value
          //Serial.println(F("LED off"));
          digitalWrite(kunci, LOW);          // will turn the LED off
          }
      }
 
   if (switchCharacteristic2.written()) 
      {
      if (switchCharacteristic2.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(starter, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(starter, LOW); //led mati
          }
      }

     
      if (switchCharacteristic3.written()) 
      {
      if (switchCharacteristic3.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(kiri, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(kiri, LOW); //led mati
          }
      }
      
      if (switchCharacteristic4.written()) 
      {
      if (switchCharacteristic4.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(bel, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(bel, LOW); //led mati
          }
      }

      if (switchCharacteristic5.written()) 
      {
      if (switchCharacteristic5.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(kanan, HIGH);            // will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(kanan, LOW); //led mati
          }
      }

      if (switchCharacteristic6.written()) 
      {
      if (switchCharacteristic6.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(kiri, HIGH);   
          digitalWrite(kanan, HIGH);// will turn the LED on
          } 
          else {                                  // a 0 value
          digitalWrite(kiri, LOW); //led mati
          digitalWrite(kanan, LOW);
          }
      }

if (switchCharacteristic7.written()) 
      {
      if (switchCharacteristic7.value()==49) {  // any value other than 0
          //Serial.println("LED on");
          digitalWrite(lampu, HIGH);   
 
          } 
          else {                                  // a 0 value
          digitalWrite(lampu, LOW); //led mati
     
          }
      }

      }

     
      
    }
  }
 
    
 
