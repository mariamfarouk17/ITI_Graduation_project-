/*
 * L298_prg.c
 *
 *  Created on: 11 Aug 2026
 *      Author: LOQ
 */
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/TIMER/TMR_int.h"
#include "L298_int.h"
#include "L298_cfg.h"

void L298_vInit(void)
{
    MDIO_vSetPinDir(DIO_PORTB, IN1, DIO_OUTPUT);
    MDIO_vSetPinDir(DIO_PORTB, IN2, DIO_OUTPUT);
    MDIO_vSetPinDir(DIO_PORTB, IN3, DIO_OUTPUT);
    MDIO_vSetPinDir(DIO_PORTB, IN4, DIO_OUTPUT);

    MDIO_vSetPinDir(DIO_PORTB, ENA, DIO_OUTPUT);
    MDIO_vSetPinDir(DIO_PORTB, ENB, DIO_OUTPUT);

    MTIMERS_vInit();
    MTIMERS_vStartTimer(TIM_0);
    MTIMERS_vStartTimer(TIM_1_A);
    MTIMERS_vSetPreloadValue(TIM_1_A, 1222u);
}



void L298_vMove(u8 Copy_u8Direction, u8 Copy_u8Speed)
{
    switch (Copy_u8Direction)
    {
        case MOVE_FORWARD:
            MDIO_vSetPinVal(DIO_PORTB, IN1, DIO_HIGH);
            MDIO_vSetPinVal(DIO_PORTB, IN2, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, IN3, DIO_HIGH);
            MDIO_vSetPinVal(DIO_PORTB, IN4, DIO_LOW);
            break;

        case MOVE_BACKWARD:
            MDIO_vSetPinVal(DIO_PORTB, IN1, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, IN2, DIO_HIGH);
            MDIO_vSetPinVal(DIO_PORTB, IN3, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, IN4, DIO_HIGH);
            break;

        case MOVE_LEFT:
            MDIO_vSetPinVal(DIO_PORTB, IN1, DIO_HIGH);
            MDIO_vSetPinVal(DIO_PORTB, IN2, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, IN3, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, IN4, DIO_HIGH);
            break;

        case MOVE_RIGHT:
            MDIO_vSetPinVal(DIO_PORTB, IN1, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, IN2, DIO_HIGH);
            MDIO_vSetPinVal(DIO_PORTB, IN3, DIO_HIGH);
            MDIO_vSetPinVal(DIO_PORTB, IN4, DIO_LOW);
            break;

        case MOVE_STOP:
        default:
            MDIO_vSetPinVal(DIO_PORTB, IN1, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, IN2, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, IN3, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, IN4, DIO_LOW);
            break;
    }

    if (Copy_u8Speed > 100u)
    {
        Copy_u8Speed = 100u;
    }

    if (Copy_u8Direction == MOVE_STOP)
    {
        MDIO_vSetPinVal(DIO_PORTB, ENA, DIO_LOW);
        MDIO_vSetPinVal(DIO_PORTD, ENB, DIO_LOW);
    }
    else
    {
        MDIO_vSetPinVal(DIO_PORTB, ENA, DIO_HIGH);
        MDIO_vSetPinVal(DIO_PORTD, ENB, DIO_HIGH);

        if (Copy_u8Speed < 100u)
        {
            u16 L_u16Preload = (u16)((100u - Copy_u8Speed) * 1222u / 100u);
            MTIMERS_vSetPreloadValue(TIM_1_A, L_u16Preload);
        }
        else
        {
            MTIMERS_vSetPreloadValue(TIM_1_A, 0u);
        }
    }
}

void L298_vMoveForward(void)
{
    L298_vMove(MOVE_FORWARD, 100u);
}

void L298_vStop(void)
{
    L298_vMove(MOVE_STOP, 0u);
}
