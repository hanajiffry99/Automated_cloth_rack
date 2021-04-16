/*
 * lcd_display.h
 *
 * Created: 4/16/2021 12:07:26 AM
 *  Author: VivoBook/Hana Jiffry
 */ 


#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>			
#include <util/delay.h>		
#include <stdlib.h>			
#include <string.h>			

#include "i2c.h"			/* include i2c header file by user define*/
#include "LCD_I2C.h"		/* include LCD header file by user define*/
#include "dh11.h"
#define Status(a,b) (a &(1<<b))>>b		/*define that part easier to use in the programme*/


void result(void);		/*define function in the programme */
void main_menu(void);	/*define function in the programme */
void reading(void);		/*define function in the programme */

char HourSt[4];

void start()
{
	i2c_init();				/* Initialization of LCD*/
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	int Hour=0;
	char data;
	
	memset(HourSt,0,4);
	
	
	lcd_cmd(0x80);					/*move cursor to the beginning of the first line */
	lcd_msg("Automated Cloth");		/* Write string on 1nd line*/
	lcd_cmd(0xC0);					/*Go to 2nd line*/
	lcd_msg("      Rack");			/* Write string on 2nd line*/
	_delay_ms(100);					/*delay 100 mile second*/
	loop1:							/*define loop for jump */
	main_menu();					/*call main menu function*/
	while(!(Status(PIND,PIND0)|Status(PIND,PIND1)|Status(PIND,PIND2))); /*wait until button press*/
	
	if(Status(PIND,PIND0))			/*if  pressed button is 1 */
	{
		lcd_cmd(0x01);				/*clear display*/
		lcd_cmd(0x80);				/*move cursor to the beginning of the first line */
		lcd_msg("Temperature = ");	/*display temperature*/
		
		int temp_value=Temp();
		if(temp_value==-1)
		lcd_msg("ERROR");
		else
		{
			itoa(temp_value,data,10);
			lcd_msg(data);
			lcd_msg("C");
		}
		
		
		lcd_cmd(0xC0);				/*2nd line*/
		lcd_msg("Humidity = ");		/*display humidity*/
		
		int hum_value=Temp();
		if(hum_value==-1)
		lcd_msg("ERROR");
		else
		{
			itoa(hum_value,data,10);
			lcd_msg(data);
			lcd_msg("%");
		}
		
		
		while(!(Status(PIND,PIND2)));	/*wait until 3rd button press*/
		{
			if(Status(PIND,PIND2))
			{
				goto loop1;				/*if 3rd button press goto main menu*/
			}
			
		}
	}
	else if(Status(PIND,PIND1))			/*go to manual mode pressing button 2 in main menu*/
	{
		while(1)
		{
			while(!(Status(PIND,PIND0)|Status(PIND,PIND1)|Status(PIND,PIND2))); /*wait pressing increment and decrement key*/
			{
				
				if(Status(PIND,PIND0))
				{
					Hour++;					/*if press increment key increment hour one by one*/
				}
				else if(Status(PIND,PIND1))
				{
					Hour--;					/*if press decrement key increment hour one by one*/
					if(Hour<0)
					{
						Hour=0;			/*hours can't decrease less than 0 */
					}
				}
			}
			itoa(Hour,HourSt,10);
			lcd_cmd(0x01);				/*clear display*/
			lcd_cmd(0x80);				/*move cursor to the beginning of the first line */
			lcd_msg("Set Work Time");	/*display string*/
			lcd_cmd(0xC0);				/*2nd line*/
			lcd_msg("      ");
			lcd_msg(HourSt);
			lcd_msg("H        ");
			
			if(Status(PIND,PIND2))
			{
				result();				/*if press 3rd button ,break */
				break;
			}
			
		}
	}
	else if (Status(PIND,PIND2))
	{
		goto loop1;						/*go to main menu*/
	}
}



void result(void)					/*result function*/
{
	lcd_cmd(0x01);				/*clear*/
	lcd_cmd(0x80);				/*move cursor to the beginning of the first line */
	lcd_msg("Rack Started");
	lcd_cmd(0xC0);
	lcd_msg("Time Ends :");
	lcd_msg(HourSt);
	lcd_msg("H");
	_delay_ms(300);
	reading();
}


void reading(void)
{
	lcd_cmd(0x01);					/*clear */
	lcd_cmd(0x80);
	lcd_msg("Temperature = ");
	lcd_cmd(0xC0);
	lcd_msg("Humidity = ");
}


void main_menu(void)
{
	lcd_cmd(0x01);
	lcd_msg("  Select Mode");
	lcd_cmd(0xC0);
	lcd_msg("1.Auto  2.Manual");
	_delay_ms(100);
}




#endif /* LCD_DISPLAY_H_ */