/*
 * GccApplication2.c
 *
 * Created: 7/10/2019 11:29:04 PM
 * Author : haseb
 */ 
/*

#include <avr/io.h>
#define  F_CPU 1000000 //clock pluse frequency
#include <util/delay.h>

void delay()
{
	//for(int i=0;i<255;i++)
	//for(int j=0;j<255;j++)
	//for(int k=0;k<100;k++)
	//;
	_delay_ms(100);
	
	
}

void reset()
{
	PORTB=0xff;
}





int main(void)
{
    // Replace with your application code 
	DDRD=0b11111111;
	PORTD=0b11111111;
	DDRA=0xFF;
	unsigned char c=1;
	DDRB=0x01;
	PORTB=c;
	
	
	
	
    while (1) 
    {
		//todo:nothing
		//PORTA=0b01111111;
		//reset();
		PORTB=c;
		//delay();
		if(c==1<<7) c=1;
		 else c=c<<1;
		//if(c) c=0;
		//else c=1;
		delay();
		  
	
    }
}


*/
	#include <avr/io.h>
	#include <avr/interrupt.h> //STEP1

	ISR(INT1_vect)//STEP2
	{
		PORTB = ~PORTB;
	}
	int main(void)
	{
		DDRB = 0xFF;
		PORTB = 0b01010101;
		GICR = (1<<INT1); //STEP3
		MCUCR = MCUCR & 0b11110011;//STEP4
		sei();//STEP5
		while(1);
	}
