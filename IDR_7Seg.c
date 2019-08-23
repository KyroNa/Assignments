/*
 * IDR_7Seg.c
 *
 *  Created on: Aug 20, 2019
 *      Author: Kyro
 */

#include "../Repo/HAL/BCDSevenSeg/BCDSevenSeg.h"
#include "../Repo/MCAL/DIO/DIO.h"
#include "../Repo/MCAL/DIO/DIO_types.h"
#include "../Repo/Library/std_types.h"
#include "avr/delay.h"

void IDR_7Seg(){

	BCDSevenSegment_Initialization();
	DIO_SetPinDirection(PORTB,Pin0,DIO_Input); //Pb0
	DIO_SetPinDirection(PORTB,Pin4,DIO_Input); //Pb1
	DIO_SetPinDirection(PORTD,Pin2,DIO_Input); //Pb2
	uint8 Value = 0;
	Std_LevelType CurrentPb0 = Std_LOW, CurrentPb1 = Std_LOW, CurrentPb2 = Std_LOW;
	Std_LevelType PreviousPb0 = Std_LOW, PreviousPb1 = Std_LOW, PreviousPb2 = Std_LOW;

	while(1) {

		//Read Pbs
		CurrentPb0 = DIO_GetPinValue(PORTB,Pin0);
		CurrentPb1 = DIO_GetPinValue(PORTB,Pin4);
		CurrentPb2 = DIO_GetPinValue(PORTD,Pin2);

		//Pb0 inc
		if ((Std_HIGH == CurrentPb0) && (Std_LOW == PreviousPb0)){
			Value ++;
			PreviousPb0 = CurrentPb0;
		}
		else if ((Std_LOW == CurrentPb0) && (Std_HIGH == PreviousPb0)) {
			PreviousPb0 = CurrentPb0;
		}

		//Pb1 dec
		if ((Std_HIGH == CurrentPb1) && (Std_LOW == PreviousPb1)){
			Value --;
			PreviousPb1 = CurrentPb1;
		}
		else if ((Std_LOW == CurrentPb1) && (Std_HIGH == PreviousPb1)) {
			PreviousPb1 = CurrentPb1;
		}

		//Pb2 reset
		if ((Std_HIGH == CurrentPb2) && (Std_LOW == PreviousPb2)){
			Value =0;
			PreviousPb2 = CurrentPb2;
		}
		else if ((Std_LOW == CurrentPb2) && (Std_HIGH == PreviousPb2)) {
			PreviousPb2 = CurrentPb2;
		}

		if (Value <100){
			if (Value<10){
			BCDSevenSegment_Write(Value);
			BCDSevenSegment_Enable2();
			}
			else {
				BCDSevenSegment_Write(Value%10);
				BCDSevenSegment_Enable2();
				_delay_ms(10);
				BCDSevenSegment_Disable2();
				BCDSevenSegment_Write(Value/10);
				BCDSevenSegment_Enable1();
				_delay_ms(10);
				BCDSevenSegment_Disable1();
			}
		}
		else {
			Value = 0;
		}
	}


}
