/*
 * LCD_int.h
 *
 *  Created on: Jul 26, 2026
 *      Author: HP
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

void HLCD_vINIT(void);

void HLCD_vSendCMD(u8 A_u8CMD);
void HLCD_vSendChar(u8 A_u8CMD);

void HLCD_vDisplayString(const u8 A_u8Str[]);

//Display a Special Character >> From CGRAM
void HLCD_vDisplaySpecialCharacter(u8 *Pattern, u8 Location, u8 Row, u8 Col);

void HLCD_vSinosoidal(u8 row, u8 col);

void HLCD_vPrintNumber(u32 A_u8Number);

void HLCD_SetCursor(u8 rown, u8 coln);

void HLCD_vClearScreen(void);

#endif /* HAL_LCD_LCD_INT_H_ */
