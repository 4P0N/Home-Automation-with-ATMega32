//#define F_CPU 8000000 // 1 MHz clock speed

#define tmpTHRS 32.0
#define lightTHRS 1.0

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

static volatile int pulse1 = 0;
static volatile int us1 = 0;


ISR(INT0_vect)
{
	if(us1 == 1)
	{
		TCCR1B = 0;
		pulse1 = TCNT1;
		TCNT1 = 0;
		us1 = 0;
	}

	else if(us1==0)
	{
		TCCR1B |= 1<<CS10;
		us1 = 1;
	}
}


int main(void)
{
	double temp = 0.0, voltage = 0.0, dist1 = 255.0, ddoor;
	int count = 0;
	
	DDRA = 0x00;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	
	ADCSRA = 0b10000001;
	
	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC00;
	sei();
	
	ddoor = 15.0;
	int state = -1;
	
	while(1)
	{
		PORTB |= 0b00010000;
		_delay_us(15);
		PORTB &= 0b11101111;
		dist1 = pulse1/58.0;
		//if(dist1 >= 0 && dist1 < 15) {
		//	PORTB |= 0b01000000;
		//}
		//else {
		//	PORTB &= 0b10111111;
		//}
		if(dist1 > 0 && dist1 < ddoor) {
			PORTB |= 0b00000010;
			if(state == 1) {
				count++;
			}
			state = 0;
		}
		else if(dist1 > 0 && dist1 < 2*ddoor) {
			PORTB |= 0b00000010;
			if(state == 0) {
				count--;
			}
			state = 1;
		}
		else {
			PORTB &= 0b11111101;
			state = -1;
		}
		
		if(count > 0) {
			PORTB |= 0b01000000;
		}
		else {
			PORTB &= 0b10111111;
		}
		_delay_ms(500);
		
		ADMUX = 0b01000001;
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		voltage = (ADC / 1024.0) * 5.0;
		if(PINA & 0b00100000) {
			if((voltage < lightTHRS) && (count > 0)) {
				PORTB |= 0b00000100;
			}
			else {
				PORTB &= 0b11111011;
			}
		}
		else {
			if(PINA & 0b00010000) {
				PORTB |= 0b00000100;
			}
			else {
				PORTB &= 0b11111011;
			}
		}
		
		
		ADMUX  = 0b01000000;
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		temp = ADC/2.5;
		if(PINA & 0b10000000) {
			if((temp > tmpTHRS) && (count > 0)) {
				PORTB |= 0b00000001;
				_delay_ms(500);
			}
			else {
				PORTB &= 0b11111110;
			}
		}
		else {
			if(PINA & 0b01000000) {
				PORTB |= 0b00000001;
				_delay_ms(500);
			}
			else {
				PORTB &= 0b11111110;
			}
		}
	}
}

