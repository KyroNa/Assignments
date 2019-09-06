/*
 * TIMER_Lab.c
 *
 *  Created on: Sep 6, 2019
 *      Author: Kyro
 */

#include "../LIB/std_types.h"
#include "../LIB/Bit_Math.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/DIO/DIO_reg.h"
#include "../MCAL/GIE/GIE.h"
#include "../MCAL/TIMER0/TIMER0.h"


volatile uint8 OV_Counter = 0;

void TIMER_OV_ISR(void)
{
	OV_Counter ++;
}

void TIMER_Lab(void)
{
	/* Led2 pin */
	DIO_SetPinDirection(PORTD,Pin3,DIO_Output);

	TIM0_Initialize();
	TIM0_OverFlowCallBack(TIMER_OV_ISR);
	TIM0_SetTimerValue(153);
	GIE_Enable();
	TIM0_OverFlowIntEnable();


	while(1)
	{
		if(OV_Counter == 60)
		{
			OV_Counter = 0;
			/* Toggle led */
			TOGGLE_BIT(PORTD_Reg,Pin3);
			TIM0_SetTimerValue(153);
		}
	}
}
