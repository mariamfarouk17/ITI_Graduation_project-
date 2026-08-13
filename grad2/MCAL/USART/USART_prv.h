/*
 * USART_prv.h
 *
 *  Created on: Aug 6, 2026
 *      Author: HP
 */

#ifndef MCAL_USART_USART_PRV_H_
#define MCAL_USART_USART_PRV_H_

#define UDR         *((volatile u8*)(0x2C))
#define UCSRA       *((volatile u8*)(0x2B))
#define UCSRB       *((volatile u8*)(0x2A))
#define UCSRC       *((volatile u8*)(0x40))
#define UBRRL       *((volatile u8*)(0x29))
#define UBRRH       *((volatile u8*)(0x40))

#endif /* MCAL_USART_USART_PRV_H_ */
