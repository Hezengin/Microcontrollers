/*
 * lcd.c
 *
 * Created: 28/02/2025 12:36:39
 *  Author: Matheus
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define LCD_E 	6  // RA6 UNI-6
#define LCD_RS	4  // RA4 UNI-6

static volatile int location = 0;

static void lcd_strobe_lcd_e(void);
static void lcd_write_string(char *str);
static void lcd_write_data(unsigned char byte);
static void lcd_write_cmd(unsigned char byte);
static void lcd_clear(void);

static void lcd_strobe_lcd_e(void) {
	PORTA |= (1<<LCD_E);	// E high
	_delay_ms(1);
	PORTA &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);
}

static void lcd_write_string(char *str) {
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

static void lcd_write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

static void lcd_write_cmd(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTA &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

static void lcd_clear(void) {
	lcd_write_cmd (0x01);
}

void init(){
	// PORTC output mode and all low (also E and RS pin)
	DDRD = 0xFF;
	DDRA = 0xFF;
	PORTC = 0x00;
	PORTA = 0x00;
	//PORTA = 0xFF;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
	_delay_ms(10);
}

void display_text(char *str){
	lcd_write_string(str);
}

void set_cursor(int position){
	lcd_clear();
	_delay_ms(2);
	location = position;
	lcd_write_cmd (0x80 + position);
}