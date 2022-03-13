#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif

#define tmpTHRS 40.0
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

	if(us1==0)
	{
		TCCR1B |= 1<<CS10;
		us1 = 1;
	}
}


int main(void)
{
	double temp = 0, voltage = 0, dist1 = 255.0;
	
	DDRA = 0x00;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	
	ADCSRA = 0b10000111;
	
	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC00;
	sei();
	
	while(1)
	{
		ADMUX = 0b00000001;
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		voltage = (ADC / 1024.0) * 5.0;
		if(PINA & 0b00100000) {
			if(voltage < lightTHRS) {
				PORTB |= 0b10000000;
			}
			else {
				PORTB &= 0b01111111;
			}
		}
		else {
			if(PINA & 0b00010000) {
				PORTB |= 0b10000000;
			}
			else {
				PORTB &= 0b01111111;
			}
		}
		
		ADMUX  = 0b00000000;
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		temp = (ADC / 1024.0) * 500.0;
		if(PINA & 0b10000000) {
			if(temp > tmpTHRS) {
				PORTB |= 0b01000000;
			}
			else {
				PORTB &= 0b10111111;
			}
		}
		else {
			if(PINA & 0b01000000) {
				PORTB |= 0b01000000;
			}
			else {
				PORTB &= 0b10111111;
			}
		}
		
		PORTB |= 1<<PORTB2;
		_delay_us(15);
		PORTB &= ~(1<<PORTB2);
		dist1 = pulse1/58.0;
		if(dist1 >= 0 && dist1 < 15) {
			PORTC |= 0b00000001;
		}
		else {
			PORTC &= 0b11111110;
		}
	}
}

