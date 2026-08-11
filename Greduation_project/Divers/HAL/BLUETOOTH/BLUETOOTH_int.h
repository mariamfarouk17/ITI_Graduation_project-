#ifndef MCAL_BLUETOOTH_BLUETOOTH_INT_H_
#define MCAL_BLUETOOTH_BLUETOOTH_INT_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/USART/USART_int.h"


void BLUETOOTH_Init(void);


void BLUETOOTH_TransmitChar(u8 A_u8Byte);



u8 BLUETOOTH_Receive(void);


#endif
