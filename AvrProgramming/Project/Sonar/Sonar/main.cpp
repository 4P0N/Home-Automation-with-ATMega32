// sonar sensor

//#define F_CPU 8000000UL


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#define dstTHRS 15.0

static volatile int p1 = 0;
static volatile int s1 = 0;

int main(void)
{
	int dist = 255;
	DDRD = 0x00;
	DDRB = 0xFF;
	//_delay_ms(50);

	//Initialise();

	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC00;

	sei();
	
	while(1)
	{
		PORTB |= 1<<PINB4;
		_delay_us(15);

		PORTB &= ~(1<<PINB4);
		dist = p1/58;

		if(dist < dstTHRS) {
			PORTB |= 0b01000000;
		}
		else {
			PORTB &= 0b10111111;
		}
	}
}

ISR(INT0_vect)
{
	if(s1 == 1)
	{
		TCCR1B = 0;
		p1 = TCNT1;
		TCNT1 = 0;
		s1 = 0;
	}

	else if(s1==0)
	{
		TCCR1B |= 1<<CS10;
		s1 = 1;
	}
}
