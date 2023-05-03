/*
 * Lab3.c
 *
 * Created: 2/6/2023 3:42:13 PM
 * Author : pined
 */ 

#include "C:/Users/pined/Documents/Atmel Studio/7.0/Lab3/F_cpu_lib.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "C:/Users/pined/Documents/Atmel Studio/7.0/Lab3/A2D_lib.h"
#include "C:/Users/pined/Documents/Atmel Studio/7.0/Lab3/LCD_lib.h"
#include "C:/Users/pined/Documents/Atmel Studio/7.0/Lab3/Serial_lib2.h"
#include "C:/Users/pined/Documents/Atmel Studio/7.0/Lab3/Motor_PWM_lib.h"

//using WASD as arrow keys
#define FORWARD 001 //W
#define LEFT 002  //A
#define STOP 004 //S
#define RIGHT 003 //D
#define SoftLEFT 005  //Z
#define SoftRIGHT 006  //X

int main(void)
{
	uint16_t valAD = 0;
	uint8_t serial_char_in;

	_delay_ms(1000); //delay
	AD_init(); // setup the analog inputs.
	USART_vInit();
	sei(); // enable interrupts
	HBridgeInit();
	uint8_t state = STOP;
	
	/* Replace with your application code */
	while (1)
	{
		uint16_t val;
		
		if(ADComplete)
		{
			val= getADval(0);
			ADComplete =0;
		}
		if(serialCheckRxComplete()!= 0)
		{
			serial_char_in = USART_vReceiveByte();
		}
		
		
		switch(state)
		{
			//HBridgeCommand...(motor 1 or 2, speed, direction)
			//0 = right motor, 1 = left motor............ 1 = forward, 0 = backwards
			case FORWARD:
			HBridgeCommand(0,95,1);
			HBridgeCommand(1,100,1);
			if(serial_char_in == 'w')
			{
				state = FORWARD;
				}
				else if(serial_char_in == 'a')
				{
				state = LEFT;
				}
				else if (serial_char_in =='d')
				{
				state = RIGHT;
				}
				else if(serial_char_in =='s')
				{
				state = STOP;
				}
				else if(serial_char_in =='z')
				{
				state = SoftLEFT;
				}
				else if(serial_char_in =='x')
				{
				state=SoftRIGHT;
				
				
			}
			break;
			
			case RIGHT:
			HBridgeCommand(0,100,1);
			HBridgeCommand(1,0,1);
			
			if(serial_char_in == 'd')
			{
			}
			else if (serial_char_in ='w')
			{
				state = FORWARD;
			}
			else if(serial_char_in == 'a')
			{
				state = LEFT;
			}
			else if (serial_char_in =='d')
			{
				state = RIGHT;
			}
			else if(serial_char_in =='s')
			{
				state = STOP;
			}
			else if(serial_char_in =='z')
			{
				state = SoftLEFT;
			}
			else if(serial_char_in =='x')
			{
				state=SoftRIGHT;
				
			}
			break;
			
		case LEFT:
		HBridgeCommand(1,100,1);
		HBridgeCommand(0,0,1);

		if(serial_char_in =='a')
		{
		}else if (serial_char_in ='w')
		{
			state = FORWARD;
		}else if(serial_char_in == 'a')
		{
			state = LEFT;
		}
		else if (serial_char_in =='d')
		{
			state = RIGHT;
		}
		else if(serial_char_in =='s')
		{
			state = STOP;
		}
		else if(serial_char_in =='z')
		{
			state = SoftLEFT;
		}
		else if(serial_char_in =='x')
		{
			state=SoftRIGHT;
	
		}
			break;
			
			case SoftRIGHT:
			HBridgeCommand(0,100,1);
			HBridgeCommand(1,60,1);
			
			if(serial_char_in =='x')
			{
			}
			else if(serial_char_in == 'a')
			{
				state = LEFT;
			}
			else if (serial_char_in =='d')
			{
				state = RIGHT;
			}
			else if(serial_char_in =='s')
			{
				state = STOP;
			}
			else if(serial_char_in =='z')
			{
				state = SoftLEFT;
			}
			else if(serial_char_in =='x')
			{
				state=SoftRIGHT;
				
			}
			break;
			
			case SoftLEFT:
			HBridgeCommand(1,100,1);
			HBridgeCommand(0,60,1);
			
			if(serial_char_in == 'z')
			{
				}
				else if(serial_char_in == 'a')
				{
				state = LEFT;
				}
				else if (serial_char_in =='d')
				{
				state = RIGHT;
				}
				else if(serial_char_in =='s')
				{
				state = STOP;
				}
				else if(serial_char_in =='z')
				{
				state = SoftLEFT;
				}
				else if(serial_char_in =='x')
				{
				state=SoftRIGHT;
				
			}
			
			break;
			
			case STOP:
			_delay_ms(1000);
			HBridgeCommand(1,0,0);
			HBridgeCommand(0,0,0);
			
			if(serial_char_in == 's')
			{
			}else if (serial_char_in ='w')
			{
				state = FORWARD;
				
			}else if(serial_char_in == 'a')
			{
				state = LEFT;
			}else if (serial_char_in =='d')
			{
				state = RIGHT;
			}
			else if(serial_char_in =='s')
			{
				state = STOP;
			}
			else if(serial_char_in =='z')
			{
				state = SoftLEFT;
			}
			else if(serial_char_in =='x')
			{
				state=SoftRIGHT;
				
			}
			
			break;
			
			//defaults to stop
			default:
			HBridgeCommand(1,0,0);
			HBridgeCommand(0,0,0);
			
			break;
		}
	}
}