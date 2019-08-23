/*
 * Counter99.c
 *
 *  Created on: Aug 20, 2019
 *      Author: Kyro
 */


#include "../Repo/MCAL/DIO/DIO.h"
#include"avr/delay.h"
#include "../Repo/HAL/BCDSevenSeg/BCDSevenSeg.h"
#include "../Repo/Library/std_types.h"

void Counter99(){
	BCDSevenSegment_Initialization();
	for (int counter=0; counter <100; counter++){
		for (int i=0; i<50; i++){
			BCDSevenSegment_WriteNumber(counter);
		}
	}
}


