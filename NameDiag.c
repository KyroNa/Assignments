/*
 * NameDiag.c
 *
 *  Created on: Aug 24, 2019
 *      Author: Kyro
 */
#include "../Repo/HAL/LCD/LCD.h"
#include "../Repo/MCAL/DIO/DIO.h"
#include "avr/delay.h"

void NameDiag() {

	//Initialization
	//set directions of LCD pins to be output
	DIO_SetPortDirection(PORTA,DIO_Output);
	DIO_SetPortDirection(PORTB,DIO_Output);

	//Initialization sequence of LCD
	LCD_Initialize();

	uint8 name[] = "Kyro";
	while(1){
		//Show name
		LCD_WriteString(name,0,0);

		//delay then clear display
		_delay_ms(1000);
		LCD_WriteCmd(0x01);

		LCD_WriteString(name,1,4);
		//delay then clear display
		_delay_ms(1000);
		LCD_WriteCmd(0x01);

		LCD_WriteString(name,0,8);
		//delay then clear display
		_delay_ms(1000);
		LCD_WriteCmd(0x01);

		LCD_WriteString(name,1,12);
		//delay then clear display
		_delay_ms(1000);
		LCD_WriteCmd(0x01);

	}

}
