/*
 * USART_int.h
 *
 *  Created on: Aug 6, 2026
 *      Author: HP
 */

#ifndef MCAL_USART_USART_INT_H_
#define MCAL_USART_USART_INT_H_

void MUSART_vINIT(void);

void MUSART_vTransmit(u8 A_u8Byte);

u8 MUSART_u8ReceiveStatus(void);

u8 MUSART_u8Receive(void);

#endif /* MCAL_USART_USART_INT_H_ */
