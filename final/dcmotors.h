/*
 * dcmotors.h
 *
 * Created: 4/15/2021 3:23:24 PM
 *  Author: VivoBook/Hana Jiffry
 */ 


#ifndef DCMOTORS_H_
#define DCMOTORS_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include<avr/io.h>
#include<util/delay.h>


void set_motors(int MotorSpeed)
{
	if(MotorSpeed > 0)
	{
		OCR0 = MotorSpeed;
		PORTD=0b00001010;//motors move forward
		_delay_ms(1000);
		
	}
	else if(MotorSpeed<0)
	{
		OCR0 = 255 + MotorSpeed;
		PORTD=0b00000101;//motors move backward
		_delay_ms(1000);
	}
	else
	{
		PORTD=0x00;//motors will stop
		_delay_ms(1000);
	}
}


void init_dc()
{
	DDRD=0xFF;
	DDRB=0XFF;
	TCCR0=(1<<WGM00)|(1<<COM01)|(1<<CS00)|(1<<CS01);
	OCR0=255;
}


#endif /* DCMOTORS_H_ */