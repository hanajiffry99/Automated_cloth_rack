/*
 * back_ultra.h
 *
 * Created: 4/17/2021 12:15:42 AM
 *  Author: VivoBook/Hana Jiffry
 */ 


#ifndef BACK_ULTRA_H_
#define BACK_ULTRA_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#define  Trigger_pin	PD0
int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;
}

double ultrasonic_back()
{
	long count;
	double distance;
	
	DDRD = 0b0000001;
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




#endif /* BACK_ULTRA_H_ */