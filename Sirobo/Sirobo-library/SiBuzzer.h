#ifndef SiBuzzer_H
#define SiBuzzer_H

#include "SiPort.h"

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define NO -1

#define A1L 221
#define A2L 248
#define A3L 278
#define A4L 294
#define A5L 330
#define A6L 371
#define A7L 416

#define A1M 441
#define A2M 495
#define A3M 556
#define A4M 589
#define A5M 661
#define A6M 742
#define A7M 833

#define A1H 882
#define A2H 990
#define A3H 1112
#define A4H 1178
#define A5H 1322
#define A6H 1484
#define A7H 1665

#define B1L 248
#define B2L 278
#define B3L 294
#define B4L 330
#define B5L 371
#define B6L 416
#define B7L 467

#define B1M 495
#define B2M 556
#define B3M 624
#define B4M 661
#define B5M 742
#define B6M 833
#define B7M 935

#define B1H 990
#define B2H 1112
#define B3H 1178
#define B4H 1322
#define B5H 1484
#define B6H 1665
#define B7H 1869

#define C1L 131
#define C2L 147
#define C3L 165
#define C4L 175
#define C5L 196
#define C6L 221
#define C7L 248

#define C1M 262
#define C2M 294
#define C3M 330
#define C4M 350
#define C5M 393
#define C6M 441
#define C7M 495

#define C1H 525
#define C2H 589
#define C3H 661
#define C4H 700
#define C5H 786
#define C6H 882
#define C7H 990

#define D1L 147
#define D2L 165
#define D3L 175
#define D4L 196
#define D5L 221
#define D6L 248
#define D7L 278

#define D1M 294
#define D2M 330
#define D3M 350
#define D4M 393
#define D5M 441
#define D6M 495
#define D7M 556

#define D1H 589
#define D2H 661
#define D3H 700
#define D4H 786
#define D5H 882
#define D6H 990
#define D7H 1112

#define E1L 165
#define E2L 175
#define E3L 196
#define E4L 221
#define E5L 248
#define E6L 278
#define E7L 312

#define E1M 330
#define E2M 350
#define E3M 393
#define E4M 441
#define E5M 495
#define E6M 556
#define E7M 624

#define E1H 661
#define E2H 700
#define E3H 786
#define E4H 882
#define E5H 990
#define E6H 1112
#define E7H 1248

#define F1L 175
#define F2L 196
#define F3L 221
#define F4L 234
#define F5L 262
#define F6L 294
#define F7L 330

#define F1M 350
#define F2M 393
#define F3M 441
#define F4M 495
#define F5M 556
#define F6M 624
#define F7M 661

#define F1H 700
#define F2H 786
#define F3H 990
#define F4H 1049
#define F5H 1178
#define F6H 1322
#define F7H 1484

#define G1L 196
#define G2L 221
#define G3L 234
#define G4L 262
#define G5L 294
#define G6L 330
#define G7L 371

#define G1M 393
#define G2M 441
#define G3M 495
#define G4M 556
#define G5M 624
#define G6M 661
#define G7M 742

#define G1H 786
#define G2H 882
#define G3H 990
#define G4H 1049
#define G5H 1178
#define G6H 1322
#define G7H 1484


extern int Tune1[] ;
extern int Tune2[] ;
extern int Tune3[] ;
extern int Beat1[] ;
extern int Beat2[] ;
extern int Beat3[] ;

class SiBuzzer :
	public SiPort
{
public:
	SiBuzzer(uint8_t port);
	void setBuzzerTone(uint16_t frequency, uint32_t duration);
	void mainkanMusik(int tuneLengt ,int *tune,int *beat);
	void mainkanMusik(int tuneLengt ,int *tune,float *beat);
	int Size(uint8_t order);
	uint8_t pin;
};
#endif