#ifndef SiRGBLed_H
#define SiRGBLed_H

#include <avr/interrupt.h>
#include <avr/io.h>
#ifndef F_CPU
#define  F_CPU 16000000UL
#endif
#include <util/delay.h>
#include <stdint.h>

#ifdef ARDUINO
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif
#endif

// If you want to use the setColorOrder functions, enable this line
#define RGB_ORDER_ON_RUNTIME

#ifdef RGB_ORDER_ON_RUNTIME	
	#define OFFSET_R(r) r+offsetRed
	#define OFFSET_G(g) g+offsetGreen
	#define OFFSET_B(b) b+offsetBlue
#else
// CHANGE YOUR STATIC RGB ORDER HERE
	#define OFFSET_R(r) r+1
	#define OFFSET_G(g) g	
	#define OFFSET_B(b) b+2	
#endif

#ifdef USE_HSV
const byte dim_curve[] = {
	0, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6,
	6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8,
	8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11,
	11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15,
	15, 15, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20,
	20, 20, 21, 21, 22, 22, 22, 23, 23, 24, 24, 25, 25, 25, 26, 26,
	27, 27, 28, 28, 29, 29, 30, 30, 31, 32, 32, 33, 33, 34, 35, 35,
	36, 36, 37, 38, 38, 39, 40, 40, 41, 42, 43, 43, 44, 45, 46, 47,
	48, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
	63, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 76, 78, 79, 81, 82,
	83, 85, 86, 88, 90, 91, 93, 94, 96, 98, 99, 101, 103, 105, 107, 109,
	110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
	146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
	193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};
#endif

struct cRGB { 
	uint8_t g; 
	uint8_t r; 
	uint8_t b;
};
	
class SiRGBLed {
public: 
	SiRGBLed(uint8_t pin, uint16_t num_leds);
	~SiRGBLed();
	
	cRGB getColorAt(uint16_t index);
	bool setColorAt(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);
	bool setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);
	bool setSubpixelAt(uint16_t index, uint8_t offset, uint8_t px_value);

	void show();
	
#ifdef RGB_ORDER_ON_RUNTIME	
	void setColorOrderRGB();
	void setColorOrderGRB();
	void setColorOrderBRG();
#endif

private:
	uint16_t count_led;
	uint8_t *pixels;

#ifdef RGB_ORDER_ON_RUNTIME	
	uint8_t offsetRed;
	uint8_t offsetGreen;
	uint8_t offsetBlue;
#endif	

	void ws2812_sendarray_mask(uint8_t *array,uint16_t length, uint8_t pinmask,uint8_t *port, uint8_t *portreg);

	const volatile uint8_t *ws2812_port;
	volatile uint8_t *ws2812_port_reg;
	uint8_t pinMask; 
};

#ifdef USE_HSV
	void SetHSV(int hue, byte sat, byte val) {
		/* convert hue, saturation and brightness ( HSB/HSV ) to RGB
		The dim_curve is used only on brightness/value and on saturation (inverted).
		This looks the most natural.
		*/

		val = dim_curve[val];
		sat = 255 - dim_curve[255 - sat];

		int base;

		if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
			r = val;
			g = val;
			b = val;
		}
		else  {
			base = ((255 - sat) * val) >> 8;

			switch (hue / 60) {
			case 0:
				r = val;
				g = (((val - base)*hue) / 60) + base;
				b = base;
				break;

			case 1:
				r = (((val - base)*(60 - (hue % 60))) / 60) + base;
				g = val;
				b = base;
				break;

			case 2:
				r = base;
				g = val;
				b = (((val - base)*(hue % 60)) / 60) + base;
				break;

			case 3:
				r = base;
				g = (((val - base)*(60 - (hue % 60))) / 60) + base;
				b = val;
				break;

			case 4:
				r = (((val - base)*(hue % 60)) / 60) + base;
				g = base;
				b = val;
				break;

			case 5:
				r = val;
				g = base;
				b = (((val - base)*(60 - (hue % 60))) / 60) + base;
				break;
			}			
		}
	}
#endif	

#endif