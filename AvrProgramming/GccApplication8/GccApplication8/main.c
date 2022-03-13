/*
 * lcd.c
 *
 * Created: 17-Jul-19 1:18:21 AM
 * Author : none
 */

#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif
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
	DDRA = 0x00;
	DDRD = 0xFF;
	DDRC = 0xFF;

	ADMUX  = 0b01100011;
	ADCSRA = 0b10000001;

	double voltage = 0;
	char display[8];

	Lcd4_Init();
	Lcd4_Clear();
	
	while(1)
	{
		ADCSRA |= (1<<ADSC);
		//Lcd4_Clear();

].]
		while(ADCSRA & (1<<ADSC));
		
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("Voltage");
		voltage = (ADC / 1024.0 /64.0) * 4.0;
		dtostrf(voltage, 5, 3, display);
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String(display);
		
	}
}



