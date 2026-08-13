/*
 * ADC_prg.c

 *
 *  Created on: Aug 2, 2026
 *      Author: HP
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "ADC_int.h"
#include "ADC_prv.h"

void MADC_vINIT(void)
{
	//AVCC
	CLR_BIT(ADMUX , 7);
	SET_BIT(ADMUX , 6);

	//RIGHT ADJUSTMENT
	CLR_BIT(ADMUX , 5);

	//PRESCALER 64
	CLR_BIT(ADCSRA , 0);
	SET_BIT(ADCSRA , 1);
	SET_BIT(ADCSRA , 2);

	//POLLING
	CLR_BIT(ADCSRA , 3);

	//SINGLE-CONVERSION MODE
	CLR_BIT(ADCSRA , 5);

	//ENABLE ADC
	SET_BIT(ADCSRA , 7);
}

//Read Value from Sensor
//Channel >> 1 , 2 , 3 , 4
u16 MADC_u16ReadAnalogValue(u8 A_u8ChannelNum)
{
	//Channel
	ADMUX = (ADMUX & 0xE0) | (A_u8ChannelNum & 0x07);

	//Start Conversion
	SET_BIT (ADCSRA , 6);

	//Wait on Flag
	while(GET_BIT (ADCSRA , 4) == 0);  // INTERRUPT FLAG

	//SET Interrupt Flag again
	SET_BIT (ADCSRA , 4);

	return ADC;

}
