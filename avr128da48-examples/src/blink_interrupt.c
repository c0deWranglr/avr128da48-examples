
#include "../include/config.h"

/*
ISR(TCA0_OVF_vect) {
	PORTC.OUTTGL = PIN6_bm;

	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
*/

void blink_interrupt_init(void) {
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	TCA0.SINGLE.PER = 0x0F00;
	TCA0.SINGLE.CTRLA = (TCA_SINGLE_CLKSEL1_bm | TCA_SINGLE_CLKSEL2_bm);
}

void blink_interrupt(void) {
	bool on = TCA0.SINGLE.CTRLA & TCA_SINGLE_ENABLE_bm;
	if (on) {
		TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_ENABLE_bm;
		cli();
		PORTC.OUTSET = PIN6_bm;
	} else {
		TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
		sei();
	}
}