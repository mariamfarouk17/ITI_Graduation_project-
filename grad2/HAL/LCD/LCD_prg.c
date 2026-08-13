/*
 * LCD_prg.c
 *
 *  Created on: Jul 26, 2026
 *      Author: HP
 */

#include <util/delay.h>

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"

#include"LCD_int.h"
#include"LCD_cfg.h"

void HLCD_vINIT(void)
{
	MDIO_vSetPortDir(LCD_DATA_PORT, DIO_PORT_OUTPUT);

	MDIO_vSetPinDir(LCD_CTRL_PORT, LCD_RS , DIO_OUTPUT);
	MDIO_vSetPinDir(LCD_CTRL_PORT, LCD_RW , DIO_OUTPUT);
	MDIO_vSetPinDir(LCD_CTRL_PORT, LCD_E , DIO_OUTPUT);

	_delay_ms(50);
	HLCD_vSendCMD(0x38);

	_delay_ms(1);
	HLCD_vSendCMD(0x0C);

	_delay_ms(1);
	HLCD_vSendCMD(0x01);

	_delay_ms(2);
	HLCD_vSendCMD(0x06);
}

void HLCD_vSendCMD(u8 A_u8CMD)
{
	//Control RS to send command
	//Connected to A0
	//RS -> 0 (Command)
	MDIO_vSetPinVal(LCD_CTRL_PORT , LCD_RS , DIO_LOW);

	//RW -> Write -> 0
	MDIO_vSetPinVal(LCD_CTRL_PORT , LCD_RW , DIO_LOW);

	//Write data
	MDIO_vSetPortVal(LCD_DATA_PORT , A_u8CMD);

	//Pulse on Enable
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_E, DIO_HIGH);
	_delay_ms(1);
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_E, DIO_LOW);
	_delay_ms(1);

}

void HLCD_vSendChar(u8 A_u8Char)
{
	/* Control RS to Send Data */
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_RS, DIO_HIGH);

	/* Reset RW to Enable Writing */
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_RW, DIO_LOW);

	/* Write instruction */
	MDIO_vSetPortVal(LCD_DATA_PORT, A_u8Char);

	/* Pulse on Enable */
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_E, DIO_HIGH);
	_delay_ms(1);
	MDIO_vSetPinVal(LCD_CTRL_PORT, LCD_E, DIO_LOW);
	_delay_ms(1);
}

void HLCD_vDisplayString(const u8 A_u8Str[])
{
	u8 L_u8Index = 0;
	for(L_u8Index = 0 ; A_u8Str[L_u8Index]!=0 ; L_u8Index ++)
	{
		HLCD_vSendChar(A_u8Str[L_u8Index]);
	}
}

//From the Datasheet to program CG RAM
void HLCD_vDisplaySpecialCharacter(u8 *Pattern, u8 Location, u8 Row, u8 Col)
{
    u8 i;

    // Step A : Set CG RAM Address
    // (Store array in CG RAM )
    HLCD_vSendCMD(0x40 + (Location * 8));

    // Step B & C : Write the 8 Rows of the Character
    // Write Data to CG RAM
    for(i = 0; i < 8; i++)
    {
        HLCD_vSendChar(Pattern[i]);
    }

    // Step D : Return to DDRAM >> SET DD RAM Address
    HLCD_SetCursor(Row, Col);

    // Step E : Display the Custom Character
    HLCD_vSendChar(Location);
}

void HLCD_vSinosoidal(u8 row, u8 col)
{
    if (row == 0)
    {
        HLCD_vSendCMD(0x80 + col);   // First row
    }
    else
    {
        HLCD_vSendCMD(0xC0 + col);   // Second row
    }
}

void HLCD_vPrintNumber(u32 A_u32Number)
{
	u8 L_u8Index = 0;
	u8 L_u8digits[10] = {0};
	while(A_u32Number > 0)
	{
		L_u8digits[L_u8Index] = (A_u32Number % 10) + '0';
		A_u32Number = A_u32Number / 10 ;
		L_u8Index ++ ;
	}

	for(s8 L_u8Index = 9 ; L_u8Index >=0 ; L_u8Index --)
	{
		if(L_u8digits[L_u8Index] == 0)
			continue;
		HLCD_vSendChar(L_u8digits[L_u8Index]);
	}
}

void HLCD_SetCursor(u8 rown, u8 coln)
{
    if (coln >= 16)   // For a 16x2 LCD
        return;

    switch (rown)
    {
        case 0:
            HLCD_vSendCMD(0x80 + coln);   // First row
            break;

        case 1:
            HLCD_vSendCMD(0xC0 + coln);   // Second row
            break;

        default:
            break;
    }
}

void HLCD_vClearScreen(void)
{
	HLCD_vSendCMD(0x01);
}
