/*
 * GccApplication1.c
 *
 * Created: 7/10/2019 8:30:19 PM
 * Author : haseb
 */ 

#include <avr/io.h>
#include<util/delay.h>

void delay(int d)
{
	//for(int i=0;i<255;i++)
	//for(int j=0;j<255;j++)
	//for(int k=0;k<100;k++)
	//;
	_delay_ms(d);
	
	
}

void reset()
{
	PORTB=0xff;
}





int main(void)
{
    /* Replace with your application code */
	DDRD=0b11111111;
	PORTD=0b11111111;
	DDRA=0xFF;
	unsigned char c=1;
	DDRB=0x01;
	
	
	
	
    while (1) 
    {
		//todo:nothing
		//PORTA=0b01111111;
		//reset();
		PORTB=c;
		//delay();
		if(c) c=0;
		c=1;
		delay(100);
		  
	
    }
}

