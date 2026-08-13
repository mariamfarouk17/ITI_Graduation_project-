/*
 * DIO_prg.c
 *
 *  Created on: Jul 23, 2026
 *      Author: HP
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "DIO_int.h"
#include "DIO_prv.h"

void MDIO_vINIT(void)
{
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;

	DDRA = 0;
	DDRB = 0;
	DDRC = 0;
	DDRD = 0;
}


//PIN Functions
//MDIO_vSetPinDir (port 0-3 , pin 0-7 , Direction 0/1)
void MDIO_vSetPinDir(u8 A_u8PortNo , u8 A_u8PinNo , u8 A_u8PinDir)
{
	//SET BIT AS OUTPUT
	if(A_u8PinDir == DIO_OUTPUT)
	{
		switch(A_u8PortNo)
		{
		case DIO_PORTA :
			SET_BIT(DDRA , A_u8PinNo);
			break;
		case DIO_PORTB :
			SET_BIT(DDRB , A_u8PinNo);
			break;
		case DIO_PORTC :
			SET_BIT(DDRC , A_u8PinNo);
			break;
		case DIO_PORTD :
			SET_BIT(DDRD , A_u8PinNo);
			break;
		}
	}
	//SET BIT AS INPUT
	else if(A_u8PinDir == DIO_INPUT)
	{
		switch(A_u8PortNo)
		{
		case DIO_PORTA :
			CLR_BIT(DDRA , A_u8PinNo);
			break;
		case DIO_PORTB :
			CLR_BIT(DDRB , A_u8PinNo);
			break;
		case DIO_PORTC :
			CLR_BIT(DDRC , A_u8PinNo);
			break;
		case DIO_PORTD :
			CLR_BIT(DDRD , A_u8PinNo);
			break;
		}
	}
}

void MDIO_vSetPinVal(u8 A_u8PortNo , u8 A_u8PinNo , u8 A_u8PinVal)
{
	//SET PIN VALUE
	if(A_u8PinVal == DIO_HIGH)
	{
		switch(A_u8PortNo)
		{
		case DIO_PORTA :
			SET_BIT(PORTA , A_u8PinNo);
			break;
		case DIO_PORTB :
			SET_BIT(PORTB , A_u8PinNo);
			break;
		case DIO_PORTC :
			SET_BIT(PORTC , A_u8PinNo);
			break;
		case DIO_PORTD :
			SET_BIT(PORTD , A_u8PinNo);
			break;
		}
	}
	else if(A_u8PinVal == DIO_LOW)
	{
		switch(A_u8PortNo)
		{
		case DIO_PORTA :
			CLR_BIT(PORTA , A_u8PinNo);
			break;
		case DIO_PORTB :
			CLR_BIT(PORTB , A_u8PinNo);
			break;
		case DIO_PORTC :
			CLR_BIT(PORTC , A_u8PinNo);
			break;
		case DIO_PORTD :
			CLR_BIT(PORTD , A_u8PinNo);
			break;
		}
	}
}

u8 MDIO_u8GetPinVal(u8 A_u8PortNo , u8 A_u8PinNo)
{
	//GET PIN VALUE
	u8 L_u8PinVal = 0;

	switch(A_u8PortNo)
	{
	case DIO_PORTA :
		L_u8PinVal = GET_BIT(PINA , A_u8PinNo);
		break;
	case DIO_PORTB :
		L_u8PinVal = GET_BIT(PINB , A_u8PinNo);
		break;
	case DIO_PORTC :
		L_u8PinVal = GET_BIT(PINC , A_u8PinNo);
		break;
	case DIO_PORTD :
		L_u8PinVal = GET_BIT(PIND , A_u8PinNo);
		break;
	}

	return L_u8PinVal;
}

void MDIO_vSetPortDir(u8 A_u8PortNo, u8 A_u8PortDir)
{

	switch(A_u8PortNo)
	{
	case DIO_PORTA:
		DDRA = A_u8PortDir;
		break;
	case DIO_PORTB:
		DDRB = A_u8PortDir;
		break;
	case DIO_PORTC:
		DDRC = A_u8PortDir;
		break;
	case DIO_PORTD:
		DDRD = A_u8PortDir;
		break;

	}
}

void MDIO_vSetPortVal(u8 A_u8PortNo, u8 A_u8PortVal)
{
	switch(A_u8PortNo)
		{
		case DIO_PORTA:
			PORTA = A_u8PortVal;
			break;
		case DIO_PORTB:
			PORTB = A_u8PortVal;
			break;
		case DIO_PORTC:
			PORTC = A_u8PortVal;
			break;
		case DIO_PORTD:
			PORTD = A_u8PortVal;
			break;

		}
}

u8 MDIO_u8GetPortVal(u8 A_u8PortNo)
{
	u8 L_u8Val = 0;
		switch(A_u8PortNo)
		{
		case DIO_PORTA:
			L_u8Val = PINA;
			break;
		case DIO_PORTB:
			L_u8Val = PINB;
			break;
		case DIO_PORTC:
			L_u8Val = PINC;
			break;
		case DIO_PORTD:
			L_u8Val = PIND;
			break;
		}
		return L_u8Val;

}

void MDIO_vTogPinVal(u8 A_u8PortNo , u8 A_u8PinNo)
{
	//TOGGLE BIT
	switch(A_u8PortNo)
	{
	case DIO_PORTA :
		TOGGLE_BIT(PORTA , A_u8PinNo);
		break;
	case DIO_PORTB :
		TOGGLE_BIT(PORTB , A_u8PinNo);
		break;
	case DIO_PORTC :
		TOGGLE_BIT(PORTC , A_u8PinNo);
		break;
	case DIO_PORTD :
		TOGGLE_BIT(PORTD , A_u8PinNo);
		break;
	}
}
