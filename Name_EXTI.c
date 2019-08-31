/*
 * Name_EXTI.c
 *
 *  Created on: Aug 31, 2019
 *      Author: Kyro
 */


#include "../Repo/MCAL/DIO/DIO.h"
#include "../Repo/HAL/LCD/LCD.h"
#include "../Repo/MCAL/EXTI/EXTI.h"
#include "../Repo/MCAL/GIE/GIE.h"
#include <util/delay.h>

uint8 flag = 1;
void ISR_Assignment();

void Name_EXTI()
{
	//Initialization
	//set directions of LCD pins to be output
	DIO_SetPortDirection(PORTA,DIO_Output);
	DIO_SetPortDirection(PORTB,DIO_Output);

	//Initialization sequence of LCD
	LCD_Initialize();

	/* Initialization */
	/* Button 2 pin */
	DIO_SetPinDirection(PORTD,2,DIO_Input);

	/* Interrupt Initialization */
	EXTI_Initialization();
	EXTI_SetCallback(ISR_Assignment);

	/* Enable PIE for INT0 */
	EXTI_EnableInt0();
	/* Enable global interrupt */
	GIE_Enable();

	uint8 name[] = "Kyro";
	uint8 row = 0;
	uint8 col = 0;

	while(1)
	{
		if(flag != 0)
		{
			for (col = 0; col < 16; col += 4)
			{
				LCD_WriteString(name,row,col);
				_delay_ms(1000);
				LCD_WriteCmd(0x01);
			}
		}
		else
		{
			for (col = 0; col < 16; col += 4)
			{
				LCD_WriteCmd(0x01);
				LCD_WriteString(name,row,col);
				_delay_ms(1000);
				row = (row ^ 1);
			}
		}
	}
}

void ISR_Assignment()
{
	flag = (flag ^ 1);
}
