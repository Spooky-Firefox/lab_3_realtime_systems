#pragma once
#include <stdint.h>

extern uint8_t times_pressed;

void setupJOYSTICK();

uint8_t is_joistick_down();

uint8_t joy_release();
