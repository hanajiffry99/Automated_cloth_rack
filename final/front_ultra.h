/*
 * front_ultra.h
 *
 * Created: 4/16/2021 11:44:06 AM
 *  Author: VivoBook
 */ 


#ifndef FRONT_ULTRA_H_
#define FRONT_ULTRA_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#define  Trigger_pin	PD1
int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;
}

double ultrasonic_front()
{
	long count;
	double distance;
	
	DDRD = 0b00000010;
	PORTD = 0xFF;
	
	sei();
	TIMSK = (1 << TOIE1);
	TCCR1A = 0;

	while(1)
	{
		
		PORTA |= (1 << Trigger_pin);
		_delay_us(10);
		PORTA &= (~(1 << Trigger_pin));
		
		TCNT1 = 0;
		TCCR1B = 0x41;
		TIFR = 1<<ICF1;
		TIFR = 1<<TOV1;

		
		
		while ((TIFR & (1 << ICF1)) == 0);
		TCNT1 = 0;
		TCCR1B = 0x01;
		TIFR = 1<<ICF1;
		TIFR = 1<<TOV1;
		TimerOverflow = 0;

		while ((TIFR & (1 << ICF1)) == 0);
		count = ICR1 + (65535 * TimerOverflow);

		distance = (double)count / 466.47;
	}
	return distance;
}




#endif /* FRONT_ULTRA_H_ */