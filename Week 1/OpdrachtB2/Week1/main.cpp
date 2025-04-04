/*
 * Week1.cpp
 */ 

#include <avr/io.h>
#define F_CPU 10e6
#include <util//delay.h>

void wait(int ms){
	for(int i = 0; i < ms; i++){
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0xC0;
    while (1) 
    {
		PORTD = 0xC0;
		wait(500);
		PORTD = 0x00;
		wait(500);
    }
}

