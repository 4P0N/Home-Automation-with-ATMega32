#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <stdlib.h>

#define enable            5
#define registerselection 6

void send_a_command(unsigned char command);
void send_a_character(unsigned char character);
void send_a_string(char *string_of_characters);

int main(void)
{
	DDRB = 0xFF;
	DDRA = 0;
	DDRD = 0xFF;
	_delay_ms(50);
	
	ADMUX |=(1<<REFS0)|(1<<REFS1);
	ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	
	int16_t COUNTA = 0;
	char SHOWA [3];
	

	send_a_command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(50);
	send_a_command(0x38);
	_delay_ms(50);
	send_a_command(0b00001111);
	_delay_ms(50);
	
	ADCSRA |=(1<<ADSC);
	while(1)
	{
		COUNTA = ADC/4;
		send_a_string ("CIRCUIT DIGEST");
		send_a_command(0x80 + 0x40 + 0);
		send_a_string ("Temp(C)=");
		send_a_command(0x80 + 0x40 + 8);
		itoa(COUNTA,SHOWA,10);
		send_a_string(SHOWA);
		send_a_string ("      ");
		send_a_command(0x80 + 0);
		
	}
}

void send_a_command(unsigned char command)
{
	PORTB = command;
	PORTD &= ~ (1<<registerselection);
	PORTD |= 1<<enable;
	_delay_ms(20);
	PORTD &= ~1<<enable;
	PORTB = 0;
}

void send_a_character(unsigned char character)
{
	PORTB = character;
	PORTD |= 1<<registerselection;
	PORTD |= 1<<enable;
	_delay_ms(20);
	PORTD &= ~1<<enable;
	PORTB = 0;
}
void send_a_string(char *string_of_characters)
{
	while(*string_of_characters > 0)
	{
		send_a_character(*string_of_characters++);
	}
}






/*#ifndef F_CPU
#define F_CPU 1600000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

#include "LCD/lcd.h"

void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0);

	// ADC Enable and prescaler of 128
	
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

// read adc value
uint16_t adc_read(uint8_t ch)
{
	// select the corresponding channel 0~7
	
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch;

	// start single conversion
	// write '1' to ADSC
	ADCSRA |= (1<<ADSC);

	// wait for conversion to complete
	// ADSC becomes '0' again
	
	while(ADCSRA & (1<<ADSC));

	return (ADC);
}

int main()
{
	DDRA=0x00;
	DDRB=0xff;
	uint16_t adc_result0;
	int temp;
	int far;
	char buffer[10];
	

	// initialize adc and lcd
	adc_init();
	lcd_init(LCD_DISP_ON_CURSOR); //CURSOR

	
	lcd_clrscr();
	lcd_gotoxy(0,0);
	
	

	_delay_ms(50);

	while(1)
	{
		adc_result0 = adc_read(0);      // read adc value at PA0
		
		temp=adc_result0/2.01;   // finding the temperature
		
		
		
		
		//lcd_gotoxy(0,0);
		//lcd_puts("Adc=");
		//itoa(adc_result0,buffer,10);   //display ADC value
		//lcd_puts(buffer);
		
		lcd_gotoxy(0,0);
		itoa(temp,buffer,10);
		lcd_puts("Temp=");   //display temperature
		lcd_puts(buffer);
		lcd_gotoxy(7,0);
		lcd_puts("C"); 
		far=(1.8*temp)+32;
		lcd_gotoxy(9,0);
		itoa(far,buffer,10);
		lcd_puts(buffer);
		lcd_gotoxy(12,0);
		lcd_puts("F");
		_delay_ms(1000);
		
		if(temp>=30)
		{lcd_clrscr();
			lcd_home();
				lcd_gotoxy(0,1);
				lcd_puts("FAN ON");
				
			PORTB=(1<<PINB0);
		
		}
		if (temp<=30)
		{
			lcd_clrscr();
			lcd_home();
			lcd_gotoxy(7,1);
			lcd_puts("FAN OFF");
			
			PORTB=(0<<PINB0);
			
		}
	}
}*/