/*
 * USART_prg.c
 *
 *  Created on: Aug 6, 2026
 *      Author: HP
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "USART_int.h"
#include "USART_prv.h"

void MUSART_vINIT(void)
{
	// Configure Full-Duplex Mode
	UCSRB = 0b00011000;

	// Enable UCSRC >> Synchronous >> No parity >> 1 Stop Bit >> 8 Bit Data >> No Clock Polarity
	UCSRC = 0b10000110;

	// BAUD RATE = 9600 >> 51 (UBRRL) , 0 (UBRRH)
	UBRRL = 51;
	UBRRH = 0;

}

void MUSART_vTransmit(u8 A_u8Byte)
{
	// Check UDR Empty
	while(! GET_BIT(UCSRA , 5));

	UDR = A_u8Byte;
}

u8 MUSART_u8ReceiveStatus(void)
{
    return GET_BIT(UCSRA, 7);
}

u8 MUSART_u8Receive(void)
{
	while(! GET_BIT(UCSRA , 7));

	return UDR;
}
