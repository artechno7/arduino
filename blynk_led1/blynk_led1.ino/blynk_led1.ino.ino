#include <BLEAttributeWithValue.h>
#include <BLECentral.h>
#include <BLECharacteristic.h>
#include <BLECommon.h>
#include <BLEDescriptor.h>
#include <BLEDevice.h>
#include <BLEPeripheral.h>
#include <BLEService.h>
#include <BLETypedCharacteristic.h>
#include <BLETypedCharacteristics.h>
#include <CurieBLE.h>

#include <Blynk.h>

#define BLYNK_PRINT Serial

#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a3cd98f0703b46be89a5c4deaa01dc49";

BLEPeripheral  blePeripheral;

void setup()
{
  // Debug console
  Serial.begin(9600);

  delay(1000);

  blePeripheral.setLocalName("Fatoni-device");
  blePeripheral.setDeviceName("Fatoni-device");
  blePeripheral.setAppearance(384);

  Blynk.begin(blePeripheral, auth);

  blePeripheral.begin();

  Serial.println("Waiting for connections...");
}

void loop()
{
  blePeripheral.poll();
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

