/*#include <avr\io.h> 
int main (void) {
	unsigned int period, duty_cycle, high_time; 
	unsigned char button; 
	DDRA = 0b00; 
	DDRB = 0xFF; // set port A for input, port B for output 
	DDRD = 0b00100000; // set pin D.5 for output (OCIA)

//1WGM11:WGM10 10: with WGM13-WGM12 to select timer mode 1110 11 Past PWM, timer 1 runs from 0 to ICR1 1/ COMIA1: COM1AO-10: clear OOKLA when compare match, Bet OOKLA when 0 
TCCR1A = 0b10000010; // compare match occurs timer OCR1A 
TCCR1B = 0b00011001; // WGM13: WGM1211; C812:C80-001: internal clock 1MHz, no prescaler

period = 20000; // PWM frequency - 50Hz period 20000us 
duty_cycle = 6; // initial duty cycle 
ICR1 = period - 1; 
high_time = (period/100) * duty_cycle; // calculation put PWM signal 
OCR1A =  high_time - 1;
//7/ get high time of output PWM signal 
 while (1){
  if (button == PINA) // ignore repeated press
   continue;
   button= PINA;
   PORTB= button;// store button press, display on port B 18
    if((button & 0b11000000) == 0b11000000) // ignore all except button SW6 and SW7 
	continue;

if ((button & 0b10000000) == 0) //Increment duty cycle it switch SW7 is pressed
	duty_cycle= (duty_cycle>1) ?duty_cycle+1: duty_cycle;


if ((button  & 0b010000000) == 0) // Increment duty cycle it switch SW6 in pressed 
	duty_cycle= (duty_cycle>1)?duty_cycle-1:duty_cycle; 
	high_time = (period/100) * duty_cycle; // calculator 
	OCR1A = high_time - 1; //Aet high time of output signal
 }
}*/

/*#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	DDRA = 0x00;
	PINA = 0x00;
	PORTD = 0;
	TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	ICR1 = 19999;

	//OCR1A = ICR1 - 2000; //18000

	//while (1)
	//{
		if(PINA & 1) {
			OCR1A = ICR1 - 800;
		}
		else if(PINA & 2) {
			OCR1A = ICR1 - 2200;
	

	#include <avr/i	}
		else {
			
		}
		_delay_ms(500);
		//OCR1A = ICR1 - 800;
		//_delay_ms(100);
		//OCR1A = ICR1 - 2200;
		//_delay_ms(100);
	//}
}*/


#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
int main(void)
{
	DDRD |= 0xFF;
	DDRA = 0x00;
	PINA = 0x11111110;
	bool b=true;
	TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	ICR1 = F_CPU;
	int aaaa = 1;
	OCR1A = ICR1 - 100; //18000
	_delay_ms(1000);

	while (1)
	{
		/*if(aaaa > 0) {
			OCR1A = ICR1 - 100; //18000
			_delay_ms(1000);
			OCR1A = ICR1 - 2200;
			_delay_ms(1000);
			aaaa--;
		}*/
		if((PINA & 0b00000001) == 0b00000001) {
			OCR1A = ICR1 - 2200;
			_delay_ms(1000);
		}
		else if((PINA & 0b00000001) == 0b00000000) {
			OCR1A = ICR1 - 100; //18000
			_delay_ms(1000);
		}
		
		//OCR1A = ICR1 - 100;
		/*if(PINA &(1<<0) & b)
		{
			OCR1A = ICR1 - 2200;
			b=false;
			//_delay_ms(100);
		}
		
		else if(PINA &(1<<1) & b)
		{
			
			OCR1A = ICR1 - 2200;
			b=false;
			//_delay_ms(100);
		}
		else if(!PINA)
		{
			b=true;
		}*/
	}
}
	



/*
Chat Conversa{
	DDRD |= 0xFF;
	DDRA = 0b11111100;
	TCCR1A |= 1<<WGM11 | 1<<COM1A1 | 1<<COM1A0;
	TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10;
	ICR1 = 19999;
	//int cnt=0;
	unsigned char ch;

	OCR1A = ICR1 - 2000; //18000

	while (1)
	{
		ch=PINA;
		if(PINA & 0b00000001)
		OCR1A = ICR1 - 800;
		else if(PINA & 0b00000010)
		//_delay_ms(100);
		OCR1A = ICR1 - 2200;
		//_delay_ms(100);
		//cnt++;
		//if(cnt>10) break;
	}

*/
//sonar sensor************************************
/*
#include <avr/io.h>
#include <MrLcd/MrLCDATmega32.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

static volatile int pulse = 0;
static volatile int i = 0;

int main(void)
{
	int16_t count_a = 0;
	char show_a[16];
	Initialise();
	DDRD = 0b11111011;
	_delay_ms(50);

	Initialise();

	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC00;

	sei();
	
	while(1)
	{
		PORTD |= 1<<PIND0;
		_delay_us(15);

		PORTD &= ~(1<<PIND0);
		count_a = pulse/58;

		Send_A_String("Distance Sensor");
		GoToMrLCDLocation(1,2);
		Send_A_String("Distance=");
		itoa(count_a,show_a,10);
		Send_A_String(show_a);
		Send_A_String(" ");
		GoToMrLCDLocation(13,2);
		Send_A_String("cm");
		GoToMrLCDLocation(1,1);
	}
}

ISR(INT0_vect)
{
	if(i == 1)
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
	}

	if(i==0)
	{
		TCCR1B |= 1<<CS10;
		i = 1;
	}
}*/
