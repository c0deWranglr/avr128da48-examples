#include <string.h>
#include "../include/logging.h"

void logging_init(void)
{
	PORTC.DIRSET = PIN0_bm;                             /* set pin 0 of PORT C (TXd) as output*/
	PORTC.DIRCLR = PIN1_bm;                             /* set pin 1 of PORT C (RXd) as input*/
	
	USART1.BAUD = (uint16_t)(USART1_BAUD_RATE(9600));   /* set the baud rate*/
	
	USART1.CTRLC = USART_CHSIZE0_bm
	| USART_CHSIZE1_bm;                    /* set the data format to 8-bit*/
	
	USART1.CTRLB |= USART_TXEN_bm;                      /* enable transmitter*/
}

void log_char(char c)
{
	while(!(USART1.STATUS & USART_DREIF_bm));
	
	USART1.TXDATAL = c;
}

void log_str(char *str)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		log_char(str[i]);
	}
}
