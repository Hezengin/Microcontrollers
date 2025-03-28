/*
 * OpdrachtB1.cpp
 *
 * Created: 21/03/2025 12:29:17
 * Author : Matheus
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <avr/delay.h>

void wait(int delay){
	for (int i = 0; i < delay; i++){
		_delay_ms(1);
	}
}

void setupADC(){
	// Internal 5 Volt, Adlar 1, Channel 0
	ADMUX = 0b01100000;
	// ADEN: ADC Enable, Adc freerunning, ADC Prescaler Select Bits : Division Factor = 64
	ADCSRA = 0b11100110;
}


int main(void)
{
	DDRF = 0x00; //PORTF input ADC
	DDRA = 0xFF; //PORTA outputs for displaying ADC value
	DDRB= 0xFF; //PORTB outputs for displaying ADC value
	
	setupADC();
	
    while (1) 
    {
		PORTA = ADCL;
		PORTB = ADCH;
		wait(100);
    }
}

