
#include "include/config.h"
#include "include/logging.h"
#include "include/switch.h"
#include "include/blink_manual.h"

int main(void) {
	logging_init();

	log_str("Starting...\r\n");

	sei();

	while (1) {
		//log_str("Testing...\r\n");
	}
}