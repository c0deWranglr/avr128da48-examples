#include "../include/blink_manual.h"

void blink_manual(void) {
	PORTC.OUTCLR = PIN6_bm;
	_delay_ms(100);
	PORTC.OUTSET = PIN6_bm;
	_delay_ms(100); //The problem with sleeping is that you can miss input events
}