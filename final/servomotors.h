/*
 * servomotors.h
 *
 * Created: 4/15/2021 8:42:03 PM
 *  Author: VivoBook
 */ 


#ifndef SERVOMOTORS_H_
#define SERVOMOTORS_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include<avr/io.h>
#include<util/delay.h>

void rotate_motors_B(int rotate_speed)
{
	if(rotate_speed==90)
	{
		OCR1B=165;
		_delay_ms(1000);
	}
	else if(rotate_speed==75)
	{
		OCR1B=120;
		_delay_ms(1000);
	}
	else if(rotate_speed==0)
	{
		OCR1B=94;
		_delay_ms(1000);
	}
	else if(rotate_speed==-90)
	{
		OCR1B=55;
		_delay_ms(1000);
	}
	else if(rotate_speed==-75)
	{
		OCR1B=68;
		_delay_ms(1000);
	}
}

void rotate_motors_A(int rotate_speed)
{
	if(rotate_speed==0)
	{
		OCR1A=94;
		_delay_ms(1000);
	}
	else if(rotate_speed==90)
	{
		OCR1A=165;
		_delay_ms(1000);
	}
	else if(rotate_speed==-90)
	{
		OCR1A=55;
		_delay_ms(1000);
	}
}


void init_servo()
{
	//Configure PWM pins OC1B and OC1A to output mode
	DDRD |= (1<<PIND4) | (1<<PIND5);
	//Clear OC1A/OC1B on compare match when up-counting and set OC1A/OC1B
	//on compare match when downcounting (sets PWM to non-inverting mode)
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1);
	//Selects prescalar value 64
	TCCR1B |= (1<<CS10) | (1<<CS11);
	//Phase Correct PWM mode is selected
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13);
	//Sets TOP value to be 250. Frequency is 500Hz
	ICR1 = 250;

}



#endif /* SERVOMOTORS_H_ */