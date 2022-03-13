#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define THRS 36.0

#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"

int main(void)
{
	double temp = 0;
	char display[8];
	char ssss[] = "Temp(C): ";

	//DDRA = 0b11111110;
	//DDRD = 0b11110000;
	//DDRC = 0b11000000;
	DDRA = 0x00;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;


	//ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	ADCSRA = 0b10000111;

	Lcd4_Init();
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String(ssss);
	
	
	//ADCSRA |=(1<<ADSC);
	while(1)
	{
		ADMUX  = 0b01000000;
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		temp = ADC/1024.0*5.0;
		if(temp > THRS) {
			PORTB |= 0b00000001;
		}
		else {
			PORTB &= 0b11111110;
		}
		dtostrf(temp, 3, 0, display);
		Lcd4_Set_Cursor(2,4);
		Lcd4_Write_String(display);
		
		_delay_ms(500);
	}
}

















/*

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <stdlib.h>
#include <lcd.h>

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
	PORTD = 0;
	
	//ADMUX |=(1<<REFS0)|(1<<REFS1);
	//ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	
	ADMUX  = 0b11000000;
	ADCSRA = 0b10000111;

	
	int COUNTA = 0;
	char SHOWA [3];
	

	send_a_command(0x01); //Clear Screen 0x01 = 00000001
	_delay_ms(50);
	send_a_command(0x38);
	_delay_ms(50);
	send_a_command(0b00001111);
	_delay_ms(50);
	
	int flag = 0;
	
	//ADCSRA |=(1<<ADSC);
	while(1)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));

		COUNTA = ADC;
		
		if(COUNTA > 36) {
			flag = 1;
		}
		else {
			flag = 0;
			//PORTD &= 0b11111110;
		}
		
		//send_a_string ("CIRCUIT DIGEST");
		//send_a_command(0x80 + 0x40 + 0);
		//send_a_string ("Temp(C)=");
		//send_a_command(0x80 + 0x40 + 8);
		itoa(COUNTA,SHOWA,10);
		send_a_string(SHOWA);
		//send_a_string ("      ");
		send_a_command(0x80 + 0);
		
		
		if(flag == 1) {
			PORTD |= 0b00000001;
		}
		else {
			PORTD &= 0b11111110;
		}
		
		_delay_ms(1000);
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

*/

/*#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <lcd.h>

//#include <MrLcd/MrLCDATmega32.h>
//#include <avr/interrupt.h>

int main(void)
{
	DDRA = 0x00;
	DDRD = 0xFF;
	DDRC = 0xFF;

	//Initialise();

	ADMUX  = 0b00000000;
	ADCSRA = 0b10000111;

	double voltage = 0;
	double temp = 0;
	
	char display[16];

	
	while(1)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		
		voltage = (ADC / 1024.0) * 5.0;
		temp = voltage * 100;
		
		
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("Temperature:");
		//voltage = (ADC / 1024.0 /64.0) * 4.0;
		dtostrf(voltage, 5, 3, display);
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String(display);
		
		if(temp > 100.0) {
			PORTD = 0b01000000;
		}
		else {
			PORTD = 0b00100000;
		}
	}
}
*/

/*
int main(void)
{
	int16_t count_a = 0;
	char show_a[16];
	Initialise();
	DDRD = 0b11111011;
	_delay_ms(50);

	Initialise();

	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC00;

	sei();
	
	while(1)
	{
		PORTD |= 1<<PIND0;
		_delay_us(15);

		PORTD &= ~(1<<PIND0);
		count_a = pulse/58;

		Send_A_String("temp Sensor");
		GoToMrLCDLocation(1,2);
		Send_A_String("temp=");
		itoa(count_a,show_a,10);
		Send_A_String(show_a);
		Send_A_String(" ");
		GoToMrLCDLocation(13,2);
		Send_A_String("C");
		GoToMrLCDLocation(1,1);
	}
}

ISR(INT0_vect)
{
	if(i == 1)
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
	}

	if(i==0)
	{
		TCCR1B |= 1<<CS10;
		i = 1;
	}
}
*/