#include <CurieBLE.h> //library
#define LED 13 // LED pada pin 13
 
BLEPeripheral blePeripheral;  // BLE Peripheral Device
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service
 
// BLE Switch Characteristic - 128-bit UUID, diatur sendiri.
BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
 
void setup() {
 
  // LED sebagai output
  pinMode(LED, OUTPUT);
 
  // atur nama BLE & UUID sesuai keinginan:
  blePeripheral.setLocalName("LEDzone");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());
 
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);
 
  // atur nilai awal
  switchCharacteristic.setValue(0);
 
  
  blePeripheral.begin();
}
 
void loop() {
  BLECentral central = blePeripheral.central();
 
  // jika client terhubung
  if (central) {
    while (central.connected()) {
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()== char(1)) {   // membaca nilai 1
          digitalWrite(LED, HIGH);         // LED menyala
        } else {                              
          digitalWrite(LED, LOW);          // LED mati
        }
      }
    }
  }
}
