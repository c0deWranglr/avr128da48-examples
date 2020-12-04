#include "../include/switch.h"

void switch_init(void) {
	PORTC.DIRCLR = PIN7_bm; // Configure as input
	PORTC.PIN7CTRL |= PORT_PULLUPEN_bm; // Enable internal pull up
}

void evaluate_press(void) {
	bool down = GPR.GPR0 & SWITCH_DOWN_bm;
	bool on = GPR.GPR0 & SWITCH_ON_bm;
	bool pressed = !(PORTC.IN & PIN7_bm);
	if (!down && pressed) {
		GPR.GPR0 |= SWITCH_DOWN_bm; //SWITCH DOWN

		if (on) {
			log_str("TOGGLE: OFF\r\n");
			GPR.GPR0 &= ~SWITCH_ON_bm; //TOGGLE OFF
			GPR.GPR0 |= SWITCH_CHANGE_bm; //STATE CHANGE
		} else {
			log_str("TOGGLE: ON\r\n");
			GPR.GPR0 |= SWITCH_ON_bm; //TOGGLE ON
			GPR.GPR0 |= SWITCH_CHANGE_bm; //STATE CHANGE
		}
	} else {
		if (down && !pressed) {
			GPR.GPR0 &= ~SWITCH_DOWN_bm; //SWITCH UP
		}
		GPR.GPR0 &= ~SWITCH_CHANGE_bm; //STATE NOT CHANGED
	}
}

bool is_on(void) {
	return GPR.GPR0 & SWITCH_ON_bm;
}

bool is_change(void) {
	return GPR.GPR0 & SWITCH_CHANGE_bm;
}