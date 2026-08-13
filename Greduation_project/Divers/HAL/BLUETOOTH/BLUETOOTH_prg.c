/*
 * BLUETOOTH_prg.c
 *
 * Created on: Aug 11, 2026
 * Author: HP
 */

#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/USART/USART_int.h"

#include "BLUETOOTH_int.h"

void HBLUETOOTH_vINIT(void)
{
	MUSART_vInit();
}

void HBLUETOOTH_vSendChar(u8 A_u8Data)
{
    MUSART_vTransmit(A_u8Data);
}

void HBLUETOOTH_vSendString(const u8 A_u8String[])
{
    u8 L_u8Index = 0;

    while(A_u8String[L_u8Index] != '\0')
    {
        HBLUETOOTH_vSendChar(A_u8String[L_u8Index]);

        L_u8Index++;
    }
}

u8 HBLUETOOTH_u8ReceiveChar(void)
{
    return MUSART_vReceive();
}

u8 HBLUETOOTH_u8DataAvailable(void)
{
    return MUSART_u8ReceiveStatus();
}
