/*
 * GccApplication1.c
 *
 * Created: 2024-01-30 14:10:46
 * Author : oller
 */ 

#include <avr/io.h>
#include "lcd.h"
#include "primes.h"
#include "tinythreads.h"
#include "joy_stick.h"

mutex blink_mut = MUTEX_INIT;
mutex joy_stick_mut = MUTEX_INIT;

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
	lock(&blink_mut);
	toggle_s1();
	unlock(&blink_mut);
}

void print_times_pressed(int pos){
	lock(&joy_stick_mut);
	if (is_joistick_down()) {
		times_pressed++;
		printAt(times_pressed,3);
	}
	unlock(&joy_stick_mut);
}


int main() {
	lock(&blink_mut);
	lock(&joy_stick_mut);

	setupLCD();
	
	spawn(print_times_pressed, 0);
	spawn(blink, 0);
	computePrimes(0);
}
