/*
 * EXTI_int.h
 *
 *  Created on: Jul 29, 2026
 *      Author: HP
 */

#ifndef MCAL_EXTI_EXTI_INT_H_
#define MCAL_EXTI_EXTI_INT_H_

#define ENABLE      1
#define DISABLE     0

#define EXTI_INT0_STATE   ENABLE
#define EXTI_INT1_STATE   ENABLE
#define EXTI_INT2_STATE   DISABLE

#define EXTI_INT0_ID     0
#define EXTI_INT1_ID     1
#define EXTI_INT2_ID     2

#define EXTI_FALLING      0
#define EXTI_RISING       1
#define EXTI_LOW_LVL      2
#define EXTI_ONCHANGE     3

#define EXTI_INT0_SENSE_CTRL   EXTI_FALLING
#define EXTI_INT1_SENSE_CTRL   EXTI_FALLING
#define EXTI_INT2_SENSE_CTRL   EXTI_FALLING


void MEXTI_vINIT(void);

void MEXTI_vCallBackFunction(void (*Fptr)(void) , u8 A_u8InterruptNo);



#endif /* MCAL_EXTI_EXTI_INT_H_ */
