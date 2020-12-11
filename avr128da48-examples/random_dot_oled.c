/*
#include "include/config.h"
#include "include/logging.h"
#include "include/switch.h"
#include "include/display.h"

#include <time.h>

uint16_t dot_color;
int x_last = 50;
int y_last = 50;
int x_pos = 50;
int y_pos = 50;

void interrupt_init(void) {
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	TCA0.SINGLE.PER = 0x0F00;
	TCA0.SINGLE.CTRLA = (TCA_SINGLE_CLKSEL1_bm | TCA_SINGLE_CLKSEL2_bm);
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

ISR(TCA0_OVF_vect)
{
	int x_next = x_pos + (rand() % 51) - 25;
	int y_next = y_pos + (rand() % 51) - 25;

	if (x_next >= 90) { x_next = 90; }
	if (x_next <= 5) { x_next = 5; }
	if (y_next >= 90) { y_next = 90; }
	if (y_next <= 5) { y_next = 5; }

	x_last = x_pos;
	y_last = y_pos;
	x_pos = x_next;
	y_pos = y_next;

	oledC_DrawCircle(x_last, y_last, 5, BACKGROUND);

	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

int _main(void)
{
	logging_init();
	switch_init();
	display_init();
	interrupt_init();

	time_t t;
	srand((unsigned) time(&t));

	log_str("Starting\r\n");
	
	dot_color = rand();
	while (1)
	{
		evaluate_press();
		if (is_change()) {
			dot_color = rand();
		}

		cli();
		oledC_DrawCircle(x_pos, y_pos, 5, dot_color);
		sei();
	}
}
*/