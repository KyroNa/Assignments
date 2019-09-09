/*
 * Servo_LCD.c
 *
 *  Created on: Sep 9, 2019
 *      Author: Kyro
 */

#include "../Nasr5_Repo/Src/LIB/Bit_Math.h"
#include "../Nasr5_Repo/Src/LIB/std_types.h"

#include "../Nasr5_Repo/Src/MCAl/DIO/DIO.h"
#include "../Nasr5_Repo/Src/MCAl/GIE/GIE.h"
#include "../Nasr5_Repo/Src/MCAl/TIMER2/TIMER2.h"

#include "../Nasr5_Repo/Src/HAL/LCD/LCD.h"
#include "../Nasr5_Repo/Src/HAL/Servo/Servo.h"

#include <stdlib.h>
#include <util/delay.h>


void Servo_LCD()
{
	/* Set pin direction for PBs */
	/* PB0 */
	DIO_SetPinDirection(PORTB,Pin0,DIO_Input);
	/* PB1 */
	DIO_SetPinDirection(PORTB,Pin4,DIO_Input);
	/* PB2 */
	DIO_SetPinDirection(PORTD,Pin2,DIO_Input);

	/*Set PBs states */
	STD_levelType Current_State_PB0 = STD_LOW;
	STD_levelType Current_State_PB1 = STD_LOW;
	STD_levelType Current_State_PB2 = STD_LOW;
	STD_levelType Previous_State_PB0 = STD_LOW;
	STD_levelType Previous_State_PB1 = STD_LOW;
	STD_levelType Previous_State_PB2 = STD_LOW;

	/* Read from PBs */
	Current_State_PB0 = DIO_GetPinValue(PORTB,Pin0);
	Current_State_PB1 = DIO_GetPinValue(PORTB,Pin4);
	Current_State_PB2 = DIO_GetPinValue(PORTD,Pin2);

	/* Initialize Servo */
	/* Set pin direction for Servo */
	DIO_SetPinDirection(PORTD,Pin7,DIO_Output);

	SERVO_Initialize();

	/* Initialize LCD */
	/* Set pin direction for LCD */
	DIO_SetPinDirection(PORTB,Pin1,DIO_Output);
	DIO_SetPinDirection(PORTB,Pin2,DIO_Output);
	DIO_SetPinDirection(PORTB,Pin3,DIO_Output);
	DIO_SetPinDirection(PORTA,Pin4,DIO_Output);
	DIO_SetPinDirection(PORTA,Pin5,DIO_Output);
	DIO_SetPinDirection(PORTA,Pin6,DIO_Output);
	DIO_SetPinDirection(PORTA,Pin7,DIO_Output);

	LCD_Initialize();

	uint8 Count = 0;
	uint8 PIN_Number[] = {0, 0, 0};
	uint8 PIN_ASCII_String[20];
	uint8 PIN_Check[] = {0, 0, 0};

	uint8 Check = 0b000;


	/* Start entering PIN */
	LCD_WriteString("Enter Pin",0,0);
	_delay_ms(500);
	itoa(PIN_Number[0],PIN_ASCII_String,10);
	LCD_WriteString(PIN_ASCII_String,1,0);
	itoa(PIN_Number[1],PIN_ASCII_String,10);
	LCD_WriteString(PIN_ASCII_String,1,1);
	itoa(PIN_Number[2],PIN_ASCII_String,10);
	LCD_WriteString(PIN_ASCII_String,1,2);

	while(Count < 3)
	{
		/* Read from PBs */
		Current_State_PB0 = DIO_GetPinValue(PORTB,Pin0);
		Current_State_PB1 = DIO_GetPinValue(PORTB,Pin4);
		Current_State_PB2 = DIO_GetPinValue(PORTD,Pin2);

		if (PIN_Number[Count] < 9)
		{
			/* Increment PIN*/
			if (Current_State_PB2 == STD_HIGH && Previous_State_PB2 == STD_LOW)
			{
				PIN_Number[Count] ++;
				Previous_State_PB2 = Current_State_PB2;
			}
			else if (Previous_State_PB2 == STD_HIGH && Current_State_PB2 == STD_LOW)
			{
				Previous_State_PB2 = Current_State_PB2;
			}
		}
		if (PIN_Number[Count] > 0)
		{
			/* Decrement PIN */
			if (Current_State_PB1 == STD_HIGH && Previous_State_PB1 == STD_LOW)
			{
				PIN_Number[Count] --;
				Previous_State_PB1 = Current_State_PB1;
			}
			else if (Previous_State_PB1 == STD_HIGH && Current_State_PB1 == STD_LOW)
			{
				Previous_State_PB1 = Current_State_PB1;
			}
		}

		/* Set next PIN */
		if (Current_State_PB0 == STD_HIGH && Previous_State_PB0 == STD_LOW)
		{
			Count ++;
			Previous_State_PB0 = Current_State_PB0;
		}
		else if (Previous_State_PB0 == STD_HIGH && Current_State_PB0 == STD_LOW)
		{
			Previous_State_PB0 = Current_State_PB0;
		}

		if (Count < 3)
		{
			/*Write PIN on LCD*/
			itoa(PIN_Number[Count],PIN_ASCII_String,10);
			LCD_WriteString(PIN_ASCII_String,1,Count);
		}
	}

	/* Clean Dsiplay */
	LCD_WriteCmd(0x01);
	_delay_ms(500);

	/* Display PIN */
	LCD_WriteString("Pin is",0,0);
	_delay_ms(500);
	itoa(PIN_Number[0],PIN_ASCII_String,10);
	LCD_WriteString(PIN_ASCII_String,1,0);
	itoa(PIN_Number[1],PIN_ASCII_String,10);
	LCD_WriteString(PIN_ASCII_String,1,1);
	itoa(PIN_Number[2],PIN_ASCII_String,10);
	LCD_WriteString(PIN_ASCII_String,1,2);
	_delay_ms(1500);

	while(1)
	{
		/* Clean Dsiplay */
		LCD_WriteCmd(0x01);
		_delay_ms(500);
		/* Ask for PIN */
		LCD_WriteString("Enter Servo Pin",0,0);
		_delay_ms(500);
		itoa(PIN_Check[0],PIN_ASCII_String,10);
		LCD_WriteString(PIN_ASCII_String,1,0);
		itoa(PIN_Check[1],PIN_ASCII_String,10);
		LCD_WriteString(PIN_ASCII_String,1,1);
		itoa(PIN_Check[2],PIN_ASCII_String,10);
		LCD_WriteString(PIN_ASCII_String,1,2);

		/* Enter PIN */
		Count = 0;

		while(Count < 3)
			{
			/* Read from PBs */
			Current_State_PB0 = DIO_GetPinValue(PORTB,Pin0);
			Current_State_PB1 = DIO_GetPinValue(PORTB,Pin4);
			Current_State_PB2 = DIO_GetPinValue(PORTD,Pin2);

			if (PIN_Check[Count] < 9)
			{
				/* Increment PIN*/
				if (Current_State_PB2 == STD_HIGH && Previous_State_PB2 == STD_LOW)
				{
					PIN_Check[Count] ++;
					Previous_State_PB2 = Current_State_PB2;
				}
				else if (Previous_State_PB2 == STD_HIGH && Current_State_PB2 == STD_LOW)
				{
					Previous_State_PB2 = Current_State_PB2;
				}
			}
			if (PIN_Check[Count] > 0)
			{
				/* Decrement PIN */
				if (Current_State_PB1 == STD_HIGH && Previous_State_PB1 == STD_LOW)
				{
					PIN_Check[Count] --;
					Previous_State_PB1 = Current_State_PB1;
				}
				else if (Previous_State_PB1 == STD_HIGH && Current_State_PB1 == STD_LOW)
				{
					Previous_State_PB1 = Current_State_PB1;
				}
			}

			/* Set next PIN */
			if (Current_State_PB0 == STD_HIGH && Previous_State_PB0 == STD_LOW)
			{
				Count ++;
				Previous_State_PB0 = Current_State_PB0;
			}
			else if (Previous_State_PB0 == STD_HIGH && Current_State_PB0 == STD_LOW)
			{
				Previous_State_PB0 = Current_State_PB0;
			}

			if (Count < 3)
			{
				/*Write PIN on LCD*/
				itoa(PIN_Check[Count],PIN_ASCII_String,10);
				LCD_WriteString(PIN_ASCII_String,1,Count);
			}
		}

		/* Check on PIN */
		/* Clean Dsiplay */
		LCD_WriteCmd(0x01);
		_delay_ms(500);

		/* Display PIN */
		LCD_WriteString("Entered Pin is",0,0);
		_delay_ms(500);
		itoa(PIN_Check[0],PIN_ASCII_String,10);
		LCD_WriteString(PIN_ASCII_String,1,0);
		itoa(PIN_Check[1],PIN_ASCII_String,10);
		LCD_WriteString(PIN_ASCII_String,1,1);
		itoa(PIN_Check[2],PIN_ASCII_String,10);
		LCD_WriteString(PIN_ASCII_String,1,2);
		_delay_ms(1500);

		/* Check on PIN */
		Count = 0;

		for(Count; Count<3; Count++)
		{
			if(PIN_Number[Count] == PIN_Check[Count])
				SET_BIT(Check,Count);
			else
				CLEAR_BIT(Check,Count);
		}

		/* Clean Dsiplay */
		LCD_WriteCmd(0x01);
		_delay_ms(500);

		if (Check == 0b111)
		{
			LCD_WriteString("Pin is correct",0,0);
			_delay_ms(500);
			LCD_WriteString("SERVO ON",1,0);
			_delay_ms(500);

			while(1)
			{
				for(uint8 Angle = 0; Angle <= 180; Angle ++)
				{
					SERVO_SetAngle(Angle);
					_delay_ms(40);
				}
			}
		}

		else
		{
			LCD_WriteString("Pin is incorrect",0,0);
			_delay_ms(500);
			LCD_WriteString("SERVO OFF",1,0);
			_delay_ms(1500);
		}
	}
}
