/*
 * LCD_cfg.h
 *
 *  Created on: Jul 26, 2026
 *      Author: HP
 */

#ifndef HAL_LCD_LCD_CFG_H_
#define HAL_LCD_LCD_CFG_H_

//Control >> 3 pins
//Data >> 8 pins

//LCD Control Port
#define LCD_CTRL_PORT   DIO_PORTB

//LCD Control Pins
#define LCD_RS          DIO_PIN0
#define LCD_RW          DIO_PIN1
#define LCD_E           DIO_PIN2

//LCD Data Port
#define LCD_DATA_PORT   DIO_PORTA

#endif /* HAL_LCD_LCD_CFG_H_ */
