/*
 * GccApplication11.cpp
 *
 * Created: 9/11/2019 5:20:54 PM
 * Author : haseb
 */ 

 #define F_CPU 8000000UL
 #include <avr/io.h>
 #define LED_OUTPUT		PORTB
 #define PIR_Input		PINC

 int main(void)
 {
	 DDRC = 0x00;	/* Set the PIR port as input port */
	 DDRB = 0xff;	/* Set the LED port as output port */

	 while(1)
	 {
		 LED_OUTPUT = PIR_Input;
	 }
 }
