/*
 * GIE_prg.c
 *
 *  Created on: Jul 29, 2026
 *      Author: HP
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"

#include"GIE_prv.h"

void MGIE_vEnableGlobalInterrupt()
{
	SET_BIT(SREG , 7);
}

void MGIE_vDisableGlobalInterrupt()
{
	CLR_BIT(SREG , 7);
}
