/*
 * TrafficLight.c
 *
 *  Created on: Aug 20, 2019
 *      Author: Kyro
 */

#include "../Repo/HAL/BCDSevenSeg/BCDSevenSeg.h"
#include "../Repo/MCAL/DIO/DIO.h"
#include "../Repo/MCAL/DIO/DIO_types.h"
#include "../Repo/Library/std_types.h"
#include "avr/delay.h"

void TrafficLight(){

	BCDSevenSegment_Initialization();
	DIO_SetPinDirection(PORTC,Pin2,DIO_Output); //Led0
	DIO_SetPinDirection(PORTC,Pin7,DIO_Output); //Led1
	DIO_SetPinDirection(PORTD,Pin3,DIO_Output); //Led2
	uint8 Value=0;

	while(1){
		Value = 60;
		for (Value = 60; Value >0; Value--){
			DIO_SetPinValue(PORTD,Pin3,Std_HIGH);
			DIO_SetPinValue(PORTC,Pin7,Std_LOW);
			DIO_SetPinValue(PORTC,Pin2,Std_LOW);
			if (Value<10){
				for (int i = 0; i<100; i++){
					BCDSevenSegment_Write(Value);
					BCDSevenSegment_Enable2();
					_delay_ms(10);
					BCDSevenSegment_Disable2();
				}
			}
			else {
				for (int i = 0; i<50; i++){
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
		}
		Value = 5;
		for (Value = 5; Value >0; Value--){
			DIO_SetPinValue(PORTD,Pin3,Std_LOW);
			DIO_SetPinValue(PORTC,Pin7,Std_HIGH);
			DIO_SetPinValue(PORTC,Pin2,Std_LOW);
			if (Value<10){
				for (int i = 0; i<100; i++){
					BCDSevenSegment_Write(Value);
					BCDSevenSegment_Enable2();
					_delay_ms(10);
					BCDSevenSegment_Disable2();
				}
			}
			else {
				for (int i = 0; i<50; i++){
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
		}
		Value = 30;
		for (Value = 30; Value >0; Value--){
			DIO_SetPinValue(PORTD,Pin3,Std_LOW);
			DIO_SetPinValue(PORTC,Pin7,Std_LOW);
			DIO_SetPinValue(PORTC,Pin2,Std_HIGH);
			if (Value<10){
				for (int i = 0; i<100; i++){
					BCDSevenSegment_Write(Value);
					BCDSevenSegment_Enable2();
					_delay_ms(10);
					BCDSevenSegment_Disable2();
				}
			}
			else {
				for (int i = 0; i<50; i++){
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
		}
	}

}
