/*
 * line_following.h
 *
 * Created: 4/16/2021 11:43:59 PM
 *  Author: VivoBook/Hana Jiffry
 */ 


#ifndef LINE_FOLLOWING_H_
#define LINE_FOLLOWING_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include<avr/io.h>
#include<util/delay.h>

#include "dcmotors.h"
#include "servomotors.h"
#include "back_ultra.h"
#include "front_ultra.h"

#define leftSen PA0                //Connect Left Sensor At PA0
#define rightSen PA1               //Connect Right Sensor At PA1

void move()
{
	DDRA=0b11110011;                // make PA0,PA1 as input for both sensors 
	DDRC=0b00001111;      // make Port  as output to connect motor pins
	
	while(1)
	{
		PINA=0x0C;             //initialize PA0 and PA1 0b00001100
		if(bit_is_clear(PINA,leftSen)){        // check if left sensor is OFF
			
			if(bit_is_clear(PINA,rightSen)) // check if right sensor is OFF
			{
				// then stop the robot
				set_motors(0);
			}
			else
			{
				// if right is ON then take left
				rotate_motors_A(-90);
				rotate_motors_B(-90);//ultrasonic turns left
				
				obstacle();//checks for obstacle
			}
		}
		
		else                                  // check if left sensor in ON
		{
			if(bit_is_clear(PINA,rightSen))
			{   // check if right sensor is OFF
				// it means left sensor is ON,so take right
				rotate_motors_A(90);
				rotate_motors_B(90); //ultrasonic turns right
				
				obstacle(); //checks for obstacle
			}
			else
			{
				// if both sensor is ON,then keep moving the robot
				set_motors(127);
				
				obstacle();
			}
		}

	}
}

void obstacle()
{
	  if(ultrasonic_front()<30)
	  {   
		  rotate_motors_B(75)
		  if(ultrasonic_front()<30)
		  {
			  rotate_motors_B(-75);
			  if(ultrasonic_front()<30)
			  {
				  if(ultrasonic_back()<30)
				  {
					  set_motors(0); //stops
				  }
				  else
				  {
					  set_motors(-225); // moves backward
					  void move();
				  }
			  }
			  else
			  {
				 rotate_motors_A(-75);
				 set_motors(127);
				 
				 void move();  
			  }
		  }
		  else
		  {
			  rotate_motors_A(75);
			  set_motors(127);
			  
			  void move();	  
		  }
	  }
	  else
	  {
		  set_motors(255);//moves forward
	  }
}


#endif /* LINE_FOLLOWING_H_ */