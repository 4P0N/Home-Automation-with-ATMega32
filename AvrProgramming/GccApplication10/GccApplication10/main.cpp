#include <avr/io.h>

//header to enable data flow control over pins

#define F_CPU 1000000

//telling controller crystal frequency attached

#include <util/delay.h>

//header to enable delay function in program



#define    E   5

//giving name �enable�  to 5th pin of PORTD, since it Is connected to LCD enable pin

#define RS  6

//giving name �registerselection� to 6th pin of PORTD, since is connected to LCD RS pin



void send_a_command(unsigned char command);

void send_a_character(unsigned char character);

void send_a_string(char *string_of_characters);

int main(void)

{

	DDRB = 0xFF;

	//putting portB and portD as output pins

	DDRD = 0xFF;

	_delay_ms(50);//giving delay of 50ms

	DDRC = 0;//Taking portC as input.

	

	ADMUX |= 0b1100000000;//setting the reference of ADC

	ADCSRA =0b01000001;

	//enabling the ADC, setting free running mode, setting prescalar 2

	float i =0;

	float LDR= 0; //storing digital output

	//char LDRSHOW [7]; //displaying digital output as resistance in 16*2 lcd

	//send_a_command(0x01); //Clear Screen 0x01 = 00000001

	//_delay_ms(50);

	//send_a_command(0x38); //telling lcd we are using 8bit command /data mode

	//_delay_ms(50);

	//send_a_command(0b00001111); //LCD SCREEN ON and courser blinking

	

	

	// send_a_string ("CIRCUIT DIGEST  ");// displaying name

	//send_a_command(0x80 + 0x40 + 0);// shifting cursor  to 1st  shell  of second line

	//send_a_string ("LDR res=");// displaying name

	//send_a_command(0x80 + 0x40 + 8);// shifting cursor  to 10th   shell  of second line

	while(1)

	{
		ADCSRA |=(1<<ADSC);  //starting the ADC conversion

		while(ADCSRA & (1<<ADSC)) {
			;
		}
		
		i=ADC/204.8;

		// Now since it�s a 10bit ADC for every Vref(5V)/1024=5mV(4.88mV) we get one digital increment or for every 1V increment in input we get 204.8 count increment. So for finding voltage at ADC pin.

		LDR = (i*10/(5-i));
		
		if(LDR<15) PORTB=0xFF;
		else PORTB=0x00;

		//  dtostrf(LDR, 4, 1, LDRSHOW);

		//send_a_string(LDRSHOW);

		//send_a_string("K   ");

		//dtostr(double precision value, width, precision, string that will store the numbers);

		// Value is either a direct value plugged into this place, or a variable to contains a value.

		//Width that is used with dtostrf is the number of characters in the number that includes the negative sign (-). For instance, if the number is -532.87, the width would be 7 including the negative sign and the decimal point.

		//Precision is how many numbers would be after the decimal point in the dtostrf usage.

		_delay_ms(500);

		// send_a_command(0x80 + 0x40 + 8);//retuning to second line 10th shell.

	}

	

}



void send_a_command(unsigned char command)

{

	PORTA = command;

	PORTD &= ~ (1<<RS); //putting 0 in RS to tell lcd we are sending command

	PORTD |= 1<<E; //telling lcd to receive command /data at the port

	_delay_ms(50);

	PORTD &= ~1<<E;//telling lcd we completed sending data

	PORTA= 0;

}



void send_a_character(unsigned char character)

{

	PORTA= character;

	PORTD |= 1<<RS;//telling LCD we are sending data not commands

	PORTD |= 1<<E;//telling LCD to start receiving command/data

	_delay_ms(50);

	PORTD &= ~1<<E;//telling lcd we completed sending data/command

	PORTA = 0;

}

void send_a_string(char *string_of_characters)

{

	while(*string_of_characters > 0)

	{

		send_a_character(*string_of_characters++);

	}

}