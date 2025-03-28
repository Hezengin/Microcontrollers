/*
 * OpdrachtB1.cpp
 *
 * Created: 21/03/2025 12:29:17
 * Author : Matheus
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <avr/delay.h>

#define BIT(x)	(1 << (x))

void wait(int delay){
	for (int i = 0; i < delay; i++){
		_delay_ms(1);
	}
}

void setupADC(){
	// Internal 5 Volt, Adlar 1, Channel 3
	ADMUX = 0b01100011;
	// ADEN: ADC Enable, ADC Prescaler Select Bits : Division Factor = 64
	ADCSRA = 0b10000110;
}


int main(void)
{
	DDRF = 0x00; //PORTF input ADC
	DDRA = 0x00;
	DDRB= 0xFF; //PORTB outputs for displaying ADC value
	
	setupADC();
	
    while (1) 
    {
		if (PINA & 0x01){
			ADCSRA |= BIT(6);				// Start ADC
			while ( ADCSRA & BIT(6) ) ;		// Wait for completion
			PORTB= ADCH;					// Show MSB (bit 9:2) of ADC
		}
		wait(100);	
    }
}

