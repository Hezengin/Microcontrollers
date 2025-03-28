/*
 * Week2.cpp
 *
 * Created: 21/02/2025 12:22:06
 * Author : Matheus
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


ISR(INT1_vect){
	PORTA <<= 1;
	if(PORTA == 0){
		PORTA = 0x01;
	}
}

ISR(INT2_vect){
	PORTA >>=1;
	if(PORTA == 0){
		PORTA = 0x80;
	}
}


int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x01;
	DDRD = 0xF0;
	EICRA |= 0x28;
	EIMSK |= 0x06;
	sei();
    while (1) 
    {
		
    }
}

