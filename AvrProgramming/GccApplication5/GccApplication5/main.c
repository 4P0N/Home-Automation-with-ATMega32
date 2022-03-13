



#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define  RowPort PORTB
#define  ColPort PORTA

#define  Drow DDRB
#define  Dcol DDRA

volatile int mode = 0;
volatile int t = 0;

unsigned char pattern[8][8] = {
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,1},
	{1,0,1,0,0,1,0,1},
	{1,1,0,0,0,0,1,1},
	{1,0,0,0,0,0,0,1}
};


ISR(INT1_vect){
	cli();
	mode ^= 1;
	_delay_ms(200);
	sei();
}

void print(char x, char y)
{
	RowPort = (1<<x);
	ColPort = ~(1<<y);
}

int main(void)
{
	Drow = 0xFF;
	Dcol = 0xFF;
	
	GICR = (1 << INT1);
	MCUCR = MCUCR | 0b00000010;
	sei();
	
	int t = 0;
	
    while (1) 
    {
		for (int k = 0; k < 100; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (pattern[(i+t)%8][j])
					{
						print(i,j);
						//_delay_ms(1);
					}
				}
			}
			RowPort = 0;
			_delay_ms(10);
		}
		
		if (mode)
		{
			t++;
			continue;
		}
		else
		{
			t = 0;
		}
		
		for (int k = 0; k < 8; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (pattern[(i+k)%8][j])
					{
						print(i,j);
						_delay_ms(1);
					}
				}
			}
			RowPort = 0;
			_delay_ms(500);
		}
		
		//print(0,1);
		//_delay_ms(1000);
		
		RowPort = 0;
		_delay_ms(1000);
    }
}

