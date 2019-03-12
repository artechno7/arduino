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
int receiver = 5; // Signal Pin of IR receiver to Arduino Digital Pin 6
int Led1=13;



IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void setup()
{ 
  irrecv.enableIRIn(); // Start the receiver
  pinMode(Led1,OUTPUT);
}

void loop()
{
if (irrecv.decode(&results)) // have we received an IR signal?

  {
    switch(results.value)

    {

      case 0xFFA25D: // 1 button pressed
                      digitalWrite(Led1,HIGH);
                      //delay(2000); 
                      break;

      case 0xFF629D: // 2 button pressed
                      digitalWrite(Led1, LOW);
                      //delay(2000); 
                      break;
                      
    }
    
      irrecv.resume(); // receive the next value
  }  


}/* --end main loop -- */
