/*
 * EXTI_prg.c
 *
 *  Created on: Jul 29, 2026
 *      Author: HP
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"

#include <util/delay.h>

#include "../../MCAL/EXTI/EXTI_int.h"
#include "../../MCAL/EXTI/EXTI_prv.h"

static void (*G_EXTI_CallBack[3])(void) = {NULL};

void MEXTI_vINIT(void)
{
#if EXTI_INT0_STATE == ENABLE

#if EXTI_INT0_SENSE_CTRL == EXTI_FALLING

	CLR_BIT(MCUCR , 0);
	SET_BIT(MCUCR , 1);

#elif EXTI_INT0_SENSE_CTRL == EXTI_RISING
	SET_BIT(MCUCR , 0);
	SET_BIT(MCUCR , 1);

#elif EXTI_INT0_SENSE_CTRL == EXTI_LOW_LVL
	CLR_BIT(MCUCR , 0);
	CLR_BIT(MCUCR , 1);

#elif EXTI_INT0_SENSE_CTRL == EXTI_ONCHANGE
	SET_BIT(MCUCR , 0);
	CLR_BIT(MCUCR , 1);

#else
#error "Sensing Control Not Available"

#endif
	SET_BIT(GICR , 6);
#endif


#if EXTI_INT1_STATE == ENABLE

#if EXTI_INT1_SENSE_CTRL == EXTI_FALLING

	CLR_BIT(MCUCR , 2);
	SET_BIT(MCUCR , 3);

#elif EXTI_INT1_SENSE_CTRL == EXTI_RISING
	SET_BIT(MCUCR , 2);
	SET_BIT(MCUCR , 3);

#elif EXTI_INT1_SENSE_CTRL == EXTI_LOW_LVL
	CLR_BIT(MCUCR , 2);
	CLR_BIT(MCUCR , 3);

#elif EXTI_INT1_SENSE_CTRL == EXTI_ONCHANGE
	SET_BIT(MCUCR , 2);
	CLR_BIT(MCUCR , 3);

#else
#error "Sensing Control Not Available"

#endif
	SET_BIT(GICR , 7);
#endif


#if EXTI_INT2_STATE == ENABLE

#if EXTI_INT2_SENSE_CTRL == EXTI_FALLING

	CLR_BIT(MCUCSR , 6);

#elif EXTI_INT1_SENSE_CTRL == EXTI_RISING
	SET_BIT(MCUCSR , 6);

#else
#error "Sensing Control Not Available"

#endif
	SET_BIT(GICR , 5);
#endif
}


void MEXTI_vCallBackFunction(void (*Fptr)(void) , u8 A_u8InterruptNo)
{
	G_EXTI_CallBack[A_u8InterruptNo] = Fptr;
}

void __vector_1(void) __attribute__((signal));   //vector_1 >> interrupt
void __vector_1(void)
{
	if(G_EXTI_CallBack[EXTI_INT0_ID] != NULL)
	{
		G_EXTI_CallBack[EXTI_INT0_ID]();
	}
}

void __vector_2(void) __attribute__((signal));   //vector_1 >> interrupt
void __vector_2(void)
{
	if(G_EXTI_CallBack[EXTI_INT1_ID] != NULL)
	{
		G_EXTI_CallBack[EXTI_INT1_ID]();
	}
}

void __vector_3(void) __attribute__((signal));   //vector_1 >> interrupt
void __vector_3(void)
{
	if(G_EXTI_CallBack[EXTI_INT2_ID] != NULL)
	{
		G_EXTI_CallBack[EXTI_INT2_ID]();
	}
}
