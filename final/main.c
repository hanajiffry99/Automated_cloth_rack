/*
 * final.c
 *
 * Created: 4/15/2021 3:20:24 PM
 * Author : VivoBook
 */ 


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>	
#include <string.h>
#include <stdlib.h>

#include "dcmotors.h"
#include "servomotors.h"
#include "dh11.h"
#include "light_left.h"
#include "light_right.h"
#include "rain.h"
#include "lcd_display.h"


int main(void)
{
	start();
	//moving some distance
	//stopping
	
	int left_light=light_value_left(),right_light=light_value_right();
	
	if(left_light>right_light)
	{
		//move to left and move forward
	}
	else if(right_light>left_light)
	{
		//move to right and move forward
	}
	else
	{
		set_motors(0);
	}
	
	int temp_value=Temp(),hum_value=Humidity(),rain=rain_value();
	
	if(temp_value>=27||hum_value>=50||rain>=10)
	{
		//move to shelter
	}
	
}

