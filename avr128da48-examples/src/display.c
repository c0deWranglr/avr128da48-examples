
#include "../include/display.h"

void display_init(void)
{
	/* -------------- PORT CONFIG --------------- */

	/* Configure OLED CS pin - PA7 as output low */
	PORTA.DIRSET |= PIN7_bm;
	PORTA.OUT &= ~PIN7_bm;

	/* Configure OLED DC pin - PD0 as output low */
	PORTD.DIRSET |= PIN0_bm;
	PORTD.OUT &= ~PIN0_bm;

	/* Configure OLED RW pin - PD3 as output low */
	PORTD.DIRSET |= PIN3_bm;
	PORTD.OUT &= ~PIN3_bm;
	
	/* Configure OLED EN pin - PD6 as output low */
	PORTD.DIRSET |= PIN6_bm;
	PORTD.OUT &= ~PIN6_bm;

	/* Configure OLED RST pin - PD7 as output low */
	PORTD.DIRSET |= PIN7_bm;
	PORTD.OUT &= ~PIN7_bm;
	
	/* -------------- SPI CONFIG --------------- */
	
	/* Configure MOSI - PA4 as output low */
	PORTA.DIRSET |= PIN4_bm;
	PORTA.OUT &= ~PIN4_bm;

	/* Configure SCK - PA6 as output low */
	PORTA.DIRSET |= PIN6_bm;
	PORTA.OUT &= ~PIN6_bm;

	oledC_setup();
	clear_screen();
}

void clear_screen(void) {
	oledC_DrawRectangle(LOWER, LOWER, UPPER, UPPER, BACKGROUND);
}