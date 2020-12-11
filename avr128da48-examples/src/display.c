
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

void draw_char(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, uint8_t ch, uint16_t color)
{
	const uint8_t *f = &font[(ch - ' ') * FONT_WIDTH]; // find the char in our font...
	uint16_t       i_x;
	uint16_t       i_y;

	for (i_x = 0; i_x < FONT_WIDTH  * sx; i_x += sx) // For each line of our text...
	{
		uint8_t curr_char_byte = f[FONT_WIDTH-i_x-1];
		for (i_y = FONT_HEIGHT * sy; i_y > 0; i_y -= sy) {
			if (curr_char_byte & 0x01) {
				oledC_DrawRectangle(y + i_y, x + i_x, y + i_y + sy - 1, x + i_x + sx - 1, color);
			}
			curr_char_byte >>= 1;
		}
	}
}

void draw_str(uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, uint8_t* string, uint16_t color) {
	int len = strlen(string);
	for (int i = len-1; i >= 0; i--) {
		draw_char(x, y, sx, sy, string[i], color);
		x += FONT_WIDTH * sx + 1;
	}
}