/*
 * GccApplication1.c
 *
 * Created: 2024-01-30 14:10:46
 * Author : oller
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "primes.h"
#include "tinythreads.h"
#include "joy_stick.h"
#include "timer.h"

// Disable interrupts
#define DISABLE()       cli()
// Enable interrupts
#define ENABLE()        sei()


void printAt(long num, int pos) {
	
	uint8_t pp = pos;
	// to create lock conflict and create issues
	// for (volatile uint16_t i = 0; i < 10000; i++){};
	writeChar( (num % 100) / 10 + '0', pp);
	pp++;
	writeChar( num % 10 + '0', pp);
}

void computePrimes(int pos) {
	long n;

	for(n = 1; ; n++) {
		if (is_prime(n)) {
			printAt(n, pos);
			// yield();
		}
	}
}

void blink(int _){
	toggle_s1();
}

void print_times_pressed(int pos){
	if (is_joistick_down()) {
		times_pressed++;
		printAt(times_pressed,3);
	}	
}


int main() {
	// setup tinythread
	initialize();
	// setup lcd
	setupLCD();
	// print 00 at pos 3, aka times pressed location
	printAt(0,3);
	// main-thread now computes primes
	computePrimes(0);
}

// joystick down interrupt
ISR(PCINT1_vect){
	spawn(print_times_pressed, 0);
}

// timer interrupt 
ISR(TIMER1_COMPA_vect){
	DISABLE();
	// when interrupt executes bit is cleared
	// TCNT1H = 0x00; // write to tmp
	// TCNT1L = 0x00; // write to lower causing temp to write to higher
	uint16_t val = read_comparator();
	// add 500 ms
	val = val + 0x0f46;
	// write higher bit
	OCR1AH = (uint8_t)(val>>8);
	// write lower bit
	OCR1AL = (uint8_t)val;
	ENABLE();
	
	spawn(blink, 0);
}
