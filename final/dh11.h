/*
 * dh11.h
 *
 * Created: 4/15/2021 10:01:06 PM
 *  Author: VivoBook/Hana Jiffry
 */ 


#ifndef DH11_H_
#define DH11_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>

#define DHT11_PIN 2
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void Request()				/* Microcontroller send start pulse/request */
{
	DDRC|= (1<<DHT11_PIN);
	PORTC &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(20);			/* wait for 20ms */
	PORTC |= (1<<DHT11_PIN);	/* set to high pin */
}

void Response()				/* receive response from DHT11 */
{
	DDRC &= ~(1<<DHT11_PIN);
	while(PINC & (1<<DHT11_PIN));
	while((PINC & (1<<DHT11_PIN))==0);
	while(PINC & (1<<DHT11_PIN));
}

uint8_t Receive_data()			/* receive data */
{
	for (int q=0; q<8; q++)
	{
		while((PINC & (1<<DHT11_PIN)) == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if(PINC & (1<<DHT11_PIN))/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(PINC & (1<<DHT11_PIN));
	}
	return c;
}

int Temp()
{
	Request();		/* send start pulse */
	Response();		/* receive response */
	I_RH=Receive_data();	/* store first eight bit in I_RH */
	D_RH=Receive_data();	/* store next eight bit in D_RH */
	I_Temp=Receive_data();	/* store next eight bit in I_Temp */
	D_Temp=Receive_data();	/* store next eight bit in D_Temp */
	CheckSum=Receive_data();/* store next eight bit in CheckSum */
	
	if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
	{
		return (-1);
	}
	
	else
	{
		return I_Temp;
	}
}

int Humidity()
{   
	Request();		/* send start pulse */
	Response();		/* receive response */
	I_RH=Receive_data();	/* store first eight bit in I_RH */
	D_RH=Receive_data();	/* store next eight bit in D_RH */
	I_Temp=Receive_data();	/* store next eight bit in I_Temp */
	D_Temp=Receive_data();	/* store next eight bit in D_Temp */
	CheckSum=Receive_data();/* store next eight bit in CheckSum */
	
	if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
	{
		return (-1);
	}
	else
	{
		return I_RH;
	}
}

#endif /* DH11_H_ */