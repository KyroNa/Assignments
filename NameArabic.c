/*
 * NameArabic.c
 *
 *  Created on: Aug 24, 2019
 *      Author: Kyro
 */


#include "../Repo/HAL/LCD/LCD.h"
#include "../Repo/MCAL/DIO/DIO.h"
#include "avr/delay.h"

void NameArabic() {

	//Initialization
	//set directions of LCD pins to be output
	DIO_SetPortDirection(PORTA,DIO_Output);
	DIO_SetPortDirection(PORTB,DIO_Output);

	//Initialization sequence of LCD
	LCD_Initialize();

	uint8 K_arabic[8] = {0x1F, 0x08, 0x04, 0x04, 0x02, 0x1F, 0x00, 0x00};
	uint8 y_arabic[8] = {0x00, 0x00, 0x00, 0x02, 0x02, 0x1F, 0x00, 0x14};
	uint8 r_arabic[8] = {0x00, 0x00, 0x00, 0x02, 0x02, 0x07, 0x08, 0x10};
	uint8 o_arabic[8] = {0x00, 0x00, 0x0E, 0x0A, 0x0E, 0x02, 0x04, 0x08};

	LCD_StoreCustomChr(K_arabic,0);
	LCD_StoreCustomChr(y_arabic,1);
	LCD_StoreCustomChr(r_arabic,2);
	LCD_StoreCustomChr(o_arabic,3);

	LCD_DisplayCustomChr(3,0,12);
	LCD_DisplayCustomChr(2,0,13);
	LCD_DisplayCustomChr(1,0,14);
	LCD_DisplayCustomChr(0,0,15);

}
