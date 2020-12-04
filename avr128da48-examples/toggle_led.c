
#include "include/config.h"
#include "include/logging.h"
#include "include/switch.h"
#include "include/blink_manual.h"

int _main(void)
{
	logging_init();
	switch_init();
	blink_timer_init();
	blink_interrupt_init();
	
	PORTC.DIRSET = PIN6_bm; //Set LED to OUTPUT
	PORTC.OUTSET = PIN6_bm; //Reset LED to OFF
	
	int pick = 0;
	while (1)
	{
		evaluate_press();

		if (pick == 0) {
			if (is_on() == true) {
				blink_manual();
			}
		}

		if (is_change() == true) {
			if (pick == 1) {
				blink_timer();
				} else if (pick == 2) {
				blink_interrupt();
			}

			if (is_on() == false) {
				pick = (pick + 1) % 3;
				if (pick == 0) { log_str("---> With Delay\r\n"); }
				else if (pick == 1) { log_str("---> With Timer\r\n"); }
				else if (pick == 2) { log_str("---> With Interrupt\r\n"); }
			}
		}
	}
}
