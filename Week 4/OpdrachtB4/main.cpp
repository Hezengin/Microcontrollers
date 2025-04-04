
#include "lcd.c"
#include <stdio.h>
void wait(int delay){
	for (int i = 0; i < delay; i++){
		_delay_ms(1);	
	}
}

void setupADC(){
	// Internal 2.56 Volt, Adlar 1, Channel 0
	ADMUX = 0b11100000;
	// ADEN: ADC Enable, Adc freerunning, ADC Prescaler Select Bits : Division Factor = 64
	ADCSRA = 0b11100110;
}

int main(void)
{
	DDRC = 0xFF; //LCD
	PORTC = 0xFF; //LCD
	
	DDRF = 0x00; // PORTF input ADC
	
	setupADC();
	init();
	char temperature[32];
	
    /* Replace with your application code */
    while (1) 
    {	
		sprintf(temperature, "Temperature: %d", (int)ADCH);
		
		set_cursor(0);
		display_text(temperature);
		
		wait(500);
    }
}

