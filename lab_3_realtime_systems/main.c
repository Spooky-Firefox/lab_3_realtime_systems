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
#include "timer.h"

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

void print_times_pressed(int pos){
	while (1){
		//  causes to inc times pressed when joystick is released
		joy_release();
		printAt((long)times_pressed,3);
	}
	
}

void blink(int _){
	while (1){
		// if 0.5 seconds since "last" 0.5 seconds, toggle s1 
		if (passed_0_5_sec()){
			toggle_s1();
		}
	}
}

int main() {
	setupLCD();
	spawn(computePrimes, 0);
	spawn(blink,0);
	print_times_pressed(3);
}
