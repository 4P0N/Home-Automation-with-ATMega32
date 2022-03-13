#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;

	//ADMUX  = 0b11000000;
	ADCSRA = 0b10000111;
	//ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

	double temp = 0;
	double voltage = 0;
	char display[8];

	Lcd4_Init();
	Lcd4_Clear();
//	Lcd4_Set_Cursor(1,1);
//	Lcd4_Write_String("Temperature(C): ");
	//Lcd4_Set_Cursor(2,1);
	//Lcd4_Write_String("-_-");
	//Lcd4_Set_Cursor(2,8);
	//Lcd4_Write_String("-_-");
	
	
	//ADCSRA |=(1<<ADSC);
	while(1)
	{
//		ADMUX  = 0b11000000;
//		ADCSRA |= (1<<ADSC);
//		while(ADCSRA & (1<<ADSC));
//		temp = ADC/4.0;
		
//		dtostrf(temp, 3, 0, display);
//		Lcd4_Set_Cursor(2,4);
//		Lcd4_Write_String(display);
		
//		if(temp > 3.0) {
//			PORTB |= 0b00000001;
//		}
//		else {
//			PORTB &= 0b11111110;
//		}
//		_delay_ms(500);
		
		
		ADMUX = 0b00000001;
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		voltage = (ADC / 1024.0) * 5.0;
		
		dtostrf(voltage, 4, 3, display);
		Lcd4_Set_Cursor(2,4);
		Lcd4_Write_String(display);
		
		if(voltage < 3.0) {
			PORTB |= 0b00000100;
		}
		else {
			PORTB &= 0b11111011;
		}
//		if(voltage < 3.0) {
//			PORTB = 0b00000100;
//		}
//		else {
//			PORTB = 0x00;
//		}

		//_delay_ms(500);
	}
}


/*
int main(void)
{
	DDRA = 0x00;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;

	//ADCSRA = 0b10000111;
	ADCSRA = 0b10000111;

	double voltage = 0, temp = 0;	
	char display[8];

	
	while(1)
	{
		//ADMUX  = 0b00000001;
		//ADCSRA |= (1<<ADSC);
		//while(ADCSRA & (1<<ADSC));
		//voltage = (ADC / 1024.0) * 5.0;
		
		ADMUX = 0b00000001;
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		voltage = (ADC / 1024.0) * 5.0;
		
		//if(PINB & 0b00000001) {
			if(voltage < 3.0) {
				PORTB = 0b00000100;
			}
			else {
				PORTB = 0x00;
			}
		//}
		//else {
		//	if(PINB & 0b00000010) {
		//		PORTB = 0b00000100;
		//	}
		//	else {
		//		PORTB = 0x00;
		//	}
		//}
	}
}
*/