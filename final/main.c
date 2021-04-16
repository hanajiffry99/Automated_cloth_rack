/*
 * final.c
 *
 * Created: 4/15/2021 3:20:24 PM
 * Author : VivoBook/Hana Jiffry
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
#include "line_following"


int main(void)
{
	start();
	move ();
	_delay_ms(5000);
	set_motors(0);
	
	int front_light=light_value_left(),back_light=light_value_right();
	
	if(front_light>back_light)
	{
		set_motors(30);
		move();
		_delay_ms(2000);
		set_motors(0);
	}
	else if(back_light>front_light)
	{
		set_motors(-230);
		move();
		_delay_ms(2000);
		set_motors(0);
	}
	else
	{
		set_motors(0);
	}
	
	int temp_value=Temp(),hum_value=Humidity(),rain=rain_value();
	
	if(temp_value>=27||hum_value>=100||rain>=10)
	{
		move();
	}
	
}

