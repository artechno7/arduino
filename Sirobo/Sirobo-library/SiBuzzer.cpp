#include "SiBuzzer.h"

//hei tayo
int Tune1[]  =  
{  
  NOTE_C4,
  NOTE_G4,
  NOTE_E4,
  NOTE_C4,
  NOTE_G4,
  NOTE_E4,
  NOTE_A4,
  NOTE_G4,
  NOTE_F4,
  NOTE_E4,
  NOTE_D4,
  NOTE_E4,
  NOTE_F4,
  0,
  
};


//生日快乐 Happy Birthday
int Tune2[]  = {
  NOTE_G4,//5
  NOTE_G4,//5
  NOTE_A4,//6
  NOTE_G4,//5
  NOTE_C5,//1
  NOTE_B4,//7
  0,
  NOTE_G4,//5
  NOTE_G4,//5
  NOTE_A4,//6
  NOTE_G4,//5
  NOTE_D5,//2
  NOTE_C5,//1
  0,
  NOTE_G4,//5
  NOTE_G4,//5
  NOTE_G5,//5
  NOTE_E5,//3
  NOTE_C5,//1
  NOTE_B4,//7
  NOTE_A4,//6
  0,
  NOTE_F5,//4
  NOTE_F5,//4
  NOTE_E5,//3
  NOTE_C5,//1
  NOTE_D5,//2
  NOTE_C5,//1
  0,
};

//欢乐颂 Ode To Joy
int Tune3[]  = {  
  NOTE_G4,//5
  NOTE_G4,//5
  NOTE_A4,//6
  NOTE_G4,//5
  NOTE_C5,//1
  NOTE_B4,//7
  0,
  NOTE_G4,//5
  NOTE_G4,//5
  NOTE_A4,//6
  NOTE_G4,//5
  NOTE_D5,//2
  NOTE_C5,//1
  0,
  NOTE_G4,//5
  NOTE_G4,//5
  NOTE_G5,//5
  NOTE_E5,//3
  NOTE_C5,//1
  NOTE_B4,//7
  NOTE_A4,//6
  0,
  NOTE_F5,//4
  NOTE_F5,//4
  NOTE_E5,//3
  NOTE_C5,//1
  NOTE_D5,//2
  NOTE_C5,//1
  0,
}; 


int Beat1[]  = {  
  8, 8, 8, 8,  8, 8, 8, 8,  8, 8, 8, 8, 8,
  4,
};


int Beat2[]  = {
  8, 8, 4, 4, 4, 4,
  4,
  8, 8, 4, 4, 4, 4,
  4,
  8, 8, 4, 4, 4, 4, 2,
  8,
  8, 8, 4, 4, 4, 2,
  4,
};

int Beat3[]  = {  
  4, 4, 4,
};

SiBuzzer::SiBuzzer(uint8_t port){	
    pin = port; 
	pinMode(pin,OUTPUT);
}

SiBuzzer::Size(uint8_t order){
	uint8_t Size;
	switch(order)
	{
		case 1:Size = sizeof(Tune1)/sizeof(Tune1[0]);break;
		case 2:Size = sizeof(Tune2)/sizeof(Tune2[0]);break;
		case 3:Size = sizeof(Tune3)/sizeof(Tune3[0]);break;
	}
	return Size;
}

void SiBuzzer::setBuzzerTone(uint16_t frequency, uint32_t duration){
	int period = 1000000L / frequency;
  	int pulse = period / 2;
  	for (long i = 0; i < duration * 1000L; i += period) 
  	{
    	digitalWrite(pin, 1);
    	delayMicroseconds(pulse);
    	digitalWrite(pin, 0);
    	delayMicroseconds(pulse);
  	}
}

void SiBuzzer::mainkanMusik(int tuneLengt ,int *tune,int *beat){
    for (int thisNote = 0; thisNote < tuneLengt; thisNote++)
    {
      int noteDuration = (1000 / beat[thisNote]);
      tone(pin, tune[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.1;
      delay(pauseBetweenNotes);
      noTone(pin);
    }
}

void SiBuzzer::mainkanMusik(int tuneLengt ,int *tune,float *beat){
    for (int thisNote = 0; thisNote < tuneLengt; thisNote++)
    {
      tone(pin,tune[thisNote]);
      delay(400*beat[thisNote]);
      noTone(pin);
    }
}