/*
 * GccApplication4.c
 *
 * Created: 7/12/2019 7:35:13 PM
 * Author : haseb
 */ 

/*
 * GccApplication1.c
 *
 * Created: 11-Jul-19 14:05:40
 * Author : ruhan
 */ 

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
	{0,0,0,0,0,0,0,0}
};


ISR(INT1_vect){
	cli();
	RowPort = 0;
	mode = 1 - mode;
	t = 0;
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
	MCUCR = MCUCR | 0b00001000;
	MCUCR = MCUCR & 0b11111011;
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		if(mode == 0) {
			for (int k = 0; k < 100; k++) {
				if(mode != 0) {break;}
				for (int i = 0; i < 8; i++) {
					//if(mode != 0) {break;}
					for (int j = 0; j < 8; j++) {
						//if(mode != 0) {break;}
						if (pattern[i][j]) {
							print(i,j);
							//_delay_ms(1);
						}
					}
				}
				RowPort = 0;
				_delay_ms(10);
			}
			RowPort = 0;
			_delay_ms(1000);
		}
		
		if(mode != 0) {
			for (int k = 0; k < 8; k++) {
				if(mode == 0) {break;}
				for (int m = 0; m < 100; m++) {
					//if(mode == 0) {break;}
					for (int i = 0; i < 8; i++) {
						//if(mode == 0) {break;}
						for (int j = 0; j < 8; j++) {
							//if(mode == 0) {break;}
							if (pattern[(i+k)%8][j]) {
								print(i,j);
								//_delay_ms(1);
							}
						}
					}
					RowPort = 0;
					_delay_ms(10);
				}
			}
		}
    }
}