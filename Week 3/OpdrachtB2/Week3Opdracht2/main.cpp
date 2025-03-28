/*
 * Week3Opdracht2.cpp
 *
 * Created: 2/28/2025 3:08:32 PM

 * Author : zengi
 */
 #include "lcd.c"
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "stdio.h"
 #include <stdbool.h>

 void wait( int ms ) {
	 for (int i=0; i<ms; i++) {
	 _delay_ms( 1 );        // library function (max 30 ms at 8MHz)
	 }
 }
 
 void timer2Init(void){
	 OCR2 = 146;
	 TCNT2 = 0;
	 TCCR2 = 0b00001101;
	 TIMSK |= (1<<7);
 }
 
 bool state = false;
 
 ISR( TIMER2_COMP_vect){
	TCNT2 = 0;
	if(state){
		OCR2 = 146;
		state = false;
	}
	else{
		OCR2 = 244;
		state = true;
	}

	PORTC ^= (1<<0);

 }
 
 int main(void)
 {
	 DDRC = 0xFF;
	 timer2Init();
	 sei();
	 while (1)
	 { 
	 }
 }
