#include <avr/io.h>

// clock 8MHz
// prescaler 1024
// inc 8MHz/1024 = 7812.5Hz
// 0.5s*7812.5(1/s) = 3906
#define DELAY_0_5_SEC 3906


void setupTIMER0A(){
	// clear timer on compare
	// wgm01 = 1
	// wgm00 = 0

	TCCR0A = 1<<WGM01;
}

uint16_t read_counter(){
       // reading lower bit, saves higher bit to tmp
       uint8_t lower = TCNT1L;
       // reading higher bit from tmp
       uint8_t higher = TCNT1H;
       // concating the bits
       return ((uint16_t)higher<<8) | (uint16_t)lower;
}

uint16_t read_comparator(){
	uint8_t lower = OCR1AL;
	uint8_t higher = OCR1AH;
	return (((uint16_t)higher)<<8) | (uint16_t)lower;
}
uint16_t next_count_value;
uint16_t prevues_count_value;

uint8_t passed_0_5_sec(){
       uint16_t cur = read_counter();
       // special case overflow
       if (prevues_count_value > next_count_value){
               if (cur > next_count_value && cur < prevues_count_value){
                       prevues_count_value = next_count_value;
                       next_count_value = next_count_value + DELAY_0_5_SEC;
                       return 1;
               }
               else {
                       return 0;
               }
       }
       else if (cur > next_count_value || cur < prevues_count_value){
               prevues_count_value = next_count_value;
               next_count_value = next_count_value + DELAY_0_5_SEC;
               return 1;
       }
       else {
               return 0;
       }
}
