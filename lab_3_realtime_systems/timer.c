#include <avr/io.h>

// clock 8MHz
// prescaler 256
// inc 8MHz/256 = 31250Hz
// 0.5s*31250(1/s) = 15625
#define DELAY_0_5_SEC 15625


void setupTIMER(){
		// use the 8 MHz system clock
		// prescaler 256
		// clkio/256 = 0b100 = 0x4
		TCCR1B = 0x4 << CS10;
}

void setupTIMER0A(){
	// clear timer on compare
	// wgm01 = 1
	// wgm00 = 0

	TCCR0A = 1<<WGM01;
}
