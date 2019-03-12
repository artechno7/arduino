#include "IRremote.h"
/*
Encoding IR Remote
library irremote.h https://github.com/z3t0/Arduino-IRremote
1  FFA25D
2 FF629D
3 FFE21D
4 FF22DD
5 FF22DD
6 FFC23D
7 FFE01F
8 FFA857
9 FF906F
* FF6897
0 FF9867
# FFB04F
UP  FF18E7
DOWN  FF4AB5
RIGHT FF5AA5
LEFT  FF10EF
OK  FF38C7
*/
int receiver = 8; // Signal Pin of IR receiver to Arduino Digital Pin 6
int Led1=13;
int Led2 = 12;
int Led3 = 11;
int Led4 = 10;

int itsONled[] = {0,0,0,0,0};
    /* the initial state of LEDs is OFF (zero) 
    the first zero must remain zero but you can 
    change the others to 1's if you want a certain
    led to light when the board is powered */


IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void setup()
{ 
  Serial.begin(9600);
  Serial.print("Led1 - Mati \n");
  Serial.print("Led2 - Mati \n");
  Serial.print("Led3 - Mati \n");
  Serial.print("Led4 - Mati \n");
  
  irrecv.enableIRIn(); // Start the receiver
  pinMode(Led1,OUTPUT);
  pinMode(Led2,OUTPUT);
  pinMode(Led3,OUTPUT);
  pinMode(Led4,OUTPUT);
}

void loop()
{
if (irrecv.decode(&results)) // have we received an IR signal?

  {
    switch(results.value)

    {

      case 0xFFA25D: // 1 button pressed
                      if(itsONled[1] == 1) {        // if first led is on then
                      digitalWrite(Led1, LOW);   // turn it off when button is pressed
                      Serial.print("Led1 - Mati \n");
                      itsONled[1] = 0;           // and set its state as off
                      } else {                      // else if first led is off
                      digitalWrite(Led1, HIGH); // turn it on when the button is pressed
                      Serial.print("Led1 - Nyala \n");
                      itsONled[1] = 1;          // and set its state as on
                      }
                      break;

      case 0xFF629D: // 2 button pressed
                      if(itsONled[2] == 1) {        // if first led is on then
                      digitalWrite(Led2, LOW);   // turn it off when button is pressed
                      Serial.print("Led2 - Mati \n");
                      itsONled[2] = 0;           // and set its state as off
                      } else {                      // else if first led is off
                      digitalWrite(Led2, HIGH); // turn it on when the button is pressed
                      Serial.print("Led2 - Nyala \n");
                      itsONled[2] = 1;          // and set its state as on
                      }
                      break;
                      
       case 0xFFE21D: // 3 button pressed
                      if(itsONled[3] == 1) {        // if first led is on then
                      digitalWrite(Led3, LOW);   // turn it off when button is pressed
                      Serial.print("Led3 - Mati \n");
                      itsONled[3] = 0;           // and set its state as off
                      } else {                      // else if first led is off
                      digitalWrite(Led3, HIGH); // turn it on when the button is pressed
                      Serial.print("Led3 - Nyala \n");
                      itsONled[3] = 1;          // and set its state as on
                      }
                      break;
                      
        case 0xFF22DD: // 4 button pressed
                      if(itsONled[4] == 1) {        // if first led is on then
                      digitalWrite(Led4, LOW);   // turn it off when button is pressed
                      Serial.print("Led4 - Mati \n");
                      itsONled[4] = 0;           // and set its state as off
                      } else {                      // else if first led is off
                      digitalWrite(Led4, HIGH); // turn it on when the button is pressed
                      Serial.print("Led4 - Nyala \n");
                      itsONled[4] = 1;          // and set its state as on
                      }
                      break;               
    }
    
      irrecv.resume(); // receive the next value
  }  


}/* --end main loop -- */
