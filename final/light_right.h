/*
 * light_right.h
 *
 * Created: 4/15/2021 11:51:44 PM
 *  Author: VivoBook/Hana Jiffry
 */ 


#ifndef LIGHT_RIGHT_H_
#define LIGHT_RIGHT_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ADC_Init_right()
{
	DDRA=0b11111101;		/*  Make ADC port as input  */
	ADCSRA = 0x87;		/*  Enable ADC, fr/128  */
}

int ADC_Read_right()
{
	ADMUX = 0x40;		/* Vref: Avcc, ADC channel: 0  */
	ADCSRA |= (1<<ADSC);	/* start conversion  */
	while ((ADCSRA &(1<<ADIF))==0);	/* monitor end of conversion interrupt flag */
	ADCSRA |=(1<<ADIF);	/* set the ADIF bit of ADCSRA register */
	return(ADCW);		/* return the ADCW */
}

float light_value_right(void)
{
	
	ADC_Init_right();		/* initialize the ADC */
	int adc_value;
	float intensity;

	while(1)
	{
		adc_value = ADC_Read_right();	/* Copy the ADC value */
		intensity = 100-(adc_value*100.00)/1023.00; /* Calculate moisture in % */
		_delay_ms(500);
	}
	return intensity;
}



#endif /* LIGHT_RIGHT_H_ */