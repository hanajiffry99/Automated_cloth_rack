/*
 * rain.h
 *
 * Created: 4/15/2021 11:45:54 PM
 *  Author: VivoBook
 */ 


#ifndef RAIN_H_
#define RAIN_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ADC_Init_rain()
{
	DDRA=0b11111011;		/*  Make ADC port as input  */
	ADCSRA = 0x87;		/*  Enable ADC, fr/128  */
}

int ADC_Read_rain()
{
	ADMUX = 0x40;		/* Vref: Avcc, ADC channel: 0  */
	ADCSRA |= (1<<ADSC);	/* start conversion  */
	while ((ADCSRA &(1<<ADIF))==0);	/* monitor end of conversion interrupt flag */
	ADCSRA |=(1<<ADIF);	/* set the ADIF bit of ADCSRA register */
	return(ADCW);		/* return the ADCW */
}

float rain_value()
{
	
	ADC_Init_rain();		/* initialize the ADC */
	int adc_value;
	float moisture;

	while(1)
	{
		adc_value = ADC_Read_rain();	/* Copy the ADC value */
		moisture = 100-(adc_value*100.00)/1023.00; /* Calculate moisture in % */
		_delay_ms(500);
	}
	return moisture;
}



#endif /* RAIN_H_ */