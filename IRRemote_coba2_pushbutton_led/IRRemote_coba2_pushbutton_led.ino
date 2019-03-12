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
    if(results.value == 0xFFA25D)
    {
      digitalWrite(Led1,HIGH);
    }
    else if(results.value == 0)
    {
      digitalWrite(Led1,LOW);
    }

   
    
      irrecv.resume(); // receive the next value
  }  


}/* --end main loop -- */
