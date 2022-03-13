// sonar sensor
#define F_CPU 1000000UL // 1 MHz clock speed

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

static volatile int pulse = 0;
static volatile int i = 0;
static volatile int p2 = 0;
static volatile int i2 = 0;
static int count=0;

ISR(INT0_vect)
{
	if(i == 1)
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
	}

	else if(i==0)
	{
		TCCR1B |= 1<<CS10;
		i = 1;
	}
}

/*ISR(INT1_vect)
{
	if(i2 == 1)
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i2 = 0;
	}

	else if(i2==0)
	{
		TCCR1B |= 1<<CS10;
		i2 = 1;
	}
}
*/

int main(void)
{
	int count_a = 255;
	DDRD = 0b11111011;
	DDRB = 0xFF;
	PORTB = 0x00;
	_delay_ms(50);

	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC00;

	sei();
	
	while(1)
	{
		PORTD |= 1<<PIND0;
		_delay_us(15);
		PORTD &= ~(1<<PIND0);
		_delay_ms(1000);
		count_a = pulse/58;

		if(count_a < 15) {
			PORTB = 0x01;
			if(count<5)
				count++;
			else if(count==5)
				count--;
		}
		else {
			PORTB = 0x00;
		}
		
		if(count==5)
			PORTB = 0x02;
		
		/*PORTD |= 1<<PIND1;
		_delay_us(15);

		PORTD &= ~(1<<PIND1);
		count2 = p2/58;

		if(count2 < 15) {
			PORTB |= 0x02;
		}
		else {
			PORTB = 0x00;
		}
		*/
	}
}

