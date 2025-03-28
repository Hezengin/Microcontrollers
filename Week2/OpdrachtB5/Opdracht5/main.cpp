

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.c"

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main( void ) {
	DDRC = 0xFF;		
	PORTC = 0xFF;

	init();
	
	char text[32];
	int i = 0;
	while (1) {
		sprintf(text, "%d seconds", i%1000);
		set_cursor(i%5);
		display_text(text);
		i++;
		wait( 1000 );
	}
	return 1;
}

