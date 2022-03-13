// door with sonar but not servo

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define tmpTHRS 36.0
#define lightTHRS 1.0

#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "lcd.h"

static volatile int pulse = 0;
static volatile int iiii = 0;



int main(void)
{
	double temp = 0, voltage = 0;
	double dist = 255.0;
//	char display[8];
	//char ssss[] = "Temp(C): ";
	
	DDRA = 0x00;
	DDRB = 0xFF;
	DDRC = 0xFF;
	//DDRD = 0xFF;
	DDRD = 0b11111011;
	
	//ADMUX  = 0b11000000;
	ADCSRA = 0b10000111;
	//ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	
	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC00;
	sei();
	
	/*TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	ICR1 = F_CPU;
	OCR1A = ICR1 - 100; //18000
	_delay_ms(1000);
	*/
//	Lcd4_Init();
//	Lcd4_Clear();
	//Lcd4_Set_Cursor(1,1);
	//Lcd4_Write_String(ssss);
	
	//ADCSRA |=(1<<ADSC);
	while(1)
	{
		PORTD |= 1<<PIND0;
		_delay_us(15);
		PORTD &= ~(1<<PIND0);
		dist = pulse/58.0;
		//if(dist < 0) {
		//	dist = 999;
		//}
		if(dist >= 0 && dist < 15) {
			PORTB |= 0b00010000;
		}
		else {
			PORTB &= 0b11101111;
		}
		//dtostrf(dist, 5, 0, display);
		//Lcd4_Set_Cursor(1,1);
		//Lcd4_Write_String(display);
		
		
		ADMUX = 0b01000001;
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		voltage = (ADC / 1024.0) * 5.0;
		if(voltage < lightTHRS) {
			PORTB |= 0b00000100;
		}
		else {
			PORTB &= 0b11111011;
		}
		//dtostrf(voltage, 4, 3, display);
		//Lcd4_Set_Cursor(2,4);
		//Lcd4_Write_String(display);
		
		ADMUX  = 0b01000000;
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		temp = (ADC / 1024.0) * 500.0;
		if(temp > tmpTHRS) {
			PORTB |= 0b00000001;
		}
		else {
			PORTB &= 0b11111110;
		}
		//dtostrf(temp, 5, 0, display);
		//Lcd4_Set_Cursor(2,1);
		//Lcd4_Write_String(display);

		//_delay_ms(500);
	}
}

ISR(INT0_vect)
{
	if(iiii == 1)
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		iiii = 0;
	}

	else if(iiii==0)
	{
		TCCR1B |= 1<<CS10;
		iiii = 1;
	}
}
