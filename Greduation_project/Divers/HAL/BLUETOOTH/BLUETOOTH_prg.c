#include "BLUETOOTH_int.h"

void BLUETOOTH_Init(void)
{
	MUSART_vInit();
}

void BLUETOOTH_Transmit(u8 A_u8Byte)
{
	MUSART_vTransmit(1000);
}

u8 BLUETOOTH_Receive(void)
{
	return 	USART_Receive();
}



