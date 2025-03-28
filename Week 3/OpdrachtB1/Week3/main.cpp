/*
 * Week3.cpp
 *
 * Created: 2/28/2025 1:47:19 PM
 * Author : zengi
 */ 
#include "lcd.c"
#include <avr/io.h>
#include "stdio.h"

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );        // library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	DDRC = 0xFF;
	DDRD&=~(1<<7);
	TCCR2=0b00000111;	// Timer 2 op normal mode starten
	
	TCNT2=0x00;			// Timer 2 resetten
	
	init();				// Init voor LCD
	
	char text[32];		// text
	while (1)
	{	
		sprintf(text, "Counts: %d", TCNT2); // updaten van de text
		set_cursor(0);	// Cursor links boven schrijven
		display_text(text); 
		
		wait(1000);
	}
	return 0;
}

