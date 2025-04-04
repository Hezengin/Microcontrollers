/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	BigAVR LCD module
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c lcd.c
**					avr-gcc -g -mmcu=atmega128 -o lcd.elf lcd.o
**					avr-objcopy -O ihex lcd.elf lcd.hex
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>



void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char symbols[16]{
	0x3F,
	0x30,
	0x5B,
	0x4F,
	0x66,
	0x6D,
	0x7D,
	0x07,
	0x7F,
	0x6F,
	0x77,
	0x7F,
	0x39,
	0x3F,
	0x79,
	0x71
};

int main( void ) {
	int count = 0;
	DDRB = 0xFF;
	DDRD = 0xF0;
	while(1){
		if(PIND &0x01 && PIND &0x02){
			count = 0;
		}
		else if(PIND & 0x01){
			count++;
			if(count > 15){
				count = 0;
			}
		}
		else if(PIND & 0x02){
			count--;
			if(count < 0){
				count = 15;
			}
		}
		
		PORTB = symbols[count];
		
		wait(200);	
	}
	return 1;
}

