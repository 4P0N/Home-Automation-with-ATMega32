#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	DDRA = 0x00;
	PINA = 0b11111110;

	TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	ICR1 = F_CPU;

	OCR1A = ICR1 - 100; //18000
	_delay_ms(1000);

	while (1)
	{
		if((PINA & 0b00000001) == 0b00000001) {
			OCR1A = ICR1 - 2200;
			_delay_ms(1000);
		}
		else if((PINA & 0b00000001) == 0b00000000) {
			OCR1A = ICR1 - 100; //18000
			_delay_ms(1000);
		}
	}
}
