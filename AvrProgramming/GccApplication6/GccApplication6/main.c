#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile int state = 0;
unsigned char pattern[8][8]={
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,1},
	{1,0,1,0,0,1,0,1},
	{1,1,0,0,0,0,1,1},
	{1,0,0,0,0,0,0,1}
};
unsigned char pattern1[8][8]={
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,1,1,0,0,1},
	{1,0,1,0,0,1,0,1},
	{1,1,0,0,0,0,1,1},
	{1,0,0,0,0,0,0,1}
};
void printLed(unsigned char a[8][8]){
	for (int i=0; i<8; i++){
		unsigned char x = 0;
		unsigned char y = 0;
		x = (1 << i);
		for(int j=0; j<8; j++){
			if(a[i][j]){
				y |= (1 << j);
			}
		}
		PORTB = x;
		PORTA = ~y;
	}
	} ISR(INT0_vect){
		state = 1 - state;
	}
	int main(void)
	{
		DDRB = 0xFF;
		DDRA = 0xFF;
		GICR = (1 << INT0); //int0 interrupt enable
		MCUCR = MCUCR | 0b00000011; //rising edge e trigger
		sei();
		//int on = 1;
		while (1)
		{
			//on = 1 - on;
			if (state == 1) {
				pattern1 = pattern1;
				int temp;
				//ekbar row shift kre print kortesi
				for (int j = 0; j < 8; j++) { //row
					temp = pattern1[0][j];
					for (int i = 0; i < 7; i++ ) { //col
						pattern1[i][j] = pattern1[i+1][j];
					} pattern1[7][j] = temp;
				}
				for (int i=0; i<255; i++) printLed(pattern1);
				//_delay_ms(500);
			}
			else if(state == 0){
				//for(int i=0; i<8; i++)
				//for(int j=0; j<8; j++) pattern1[i][j] = pattern[i][j];
				for (int i=0; i<255; i++)printLed(pattern);
				PORTB = 0xFF; //led off
				_delay_ms(500);
			}
		}
	}

