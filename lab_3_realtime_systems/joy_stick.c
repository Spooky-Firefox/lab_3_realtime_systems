#include <avr/io.h>
// joystick press is on portB bit 5
// 0x0001_0000 = 0x40
#define JOY_PRESS_MASK 0x10
#define JOY_PRESS_BIT 4

uint8_t times_pressed = 0;
uint8_t last_joy_state = 0;

void setupJOYSTICK(){
	// configure the controll register

	// set to input, DDRB bit 7 zero
	// set the pull up resistor PORTB bit 7 one
	PORTB = PORTB | (1<<JOY_PRESS_BIT);
	// PORTB = 0xff;
	last_joy_state = 0;
	times_pressed = 0;
}

// returns true if joystick is down false if not
uint8_t is_joistick_down(){
	return (PINB & JOY_PRESS_MASK) != JOY_PRESS_MASK;
}




uint8_t joy_release(){
	uint8_t now = is_joistick_down();
	// swaps the toggles of s3 and s4 button goes from pressed to not pressed
	if (now == 0 && last_joy_state == 1){
		last_joy_state = now;
		times_pressed++;
		return 1;
	}
	last_joy_state = now;
	return 0;
}
