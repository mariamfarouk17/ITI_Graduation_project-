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

    MDIO_vSetPinDir(DIO_PORTA, ENA, DIO_OUTPUT);
    MDIO_vSetPinDir(DIO_PORTB, ENB, DIO_OUTPUT);

    MTIMERS_vInit();
    MTIMERS_vStartTimer(TIM_0);
    /* Start Timer1 (used for motor PWM) */
    MTIMERS_vStartTimer(TIM_1);
    /* Initialize both compare channels A and B */
    MTIMERS_vSetCompareMatch(TIM_1_A, 1222u);
    MTIMERS_vSetCompareMatch(TIM_1_B, 1222u);
}



void L298_vMove(u8 Copy_u8Direction, u8 Copy_u8Speed)
{
    L298_vMoveDualSpeed(Copy_u8Direction, Copy_u8Speed, Copy_u8Speed);
}

void L298_vMoveDualSpeed(u8 Copy_u8Direction, u8 Copy_u8SpeedLeft, u8 Copy_u8SpeedRight)
{
    /* Set motor direction pins based on requested direction */
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

    /* Clamp speeds */
    if (Copy_u8SpeedLeft > 100u) Copy_u8SpeedLeft = 100u;
    if (Copy_u8SpeedRight > 100u) Copy_u8SpeedRight = 100u;

    /* Enable/disable motor outputs */
    if (Copy_u8Direction == MOVE_STOP)
    {
        MDIO_vSetPinVal(DIO_PORTA, ENA, DIO_LOW);
        MDIO_vSetPinVal(DIO_PORTB, ENB, DIO_LOW);
    }
    else
    {
        MDIO_vSetPinVal(DIO_PORTA, ENA, DIO_HIGH);
        MDIO_vSetPinVal(DIO_PORTB, ENB, DIO_HIGH);

        /* Convert speed (0-100) to compare value */
        u16 L_u16PreloadA = (u16)((100u - Copy_u8SpeedLeft) * 1222u / 100u);
        u16 L_u16PreloadB = (u16)((100u - Copy_u8SpeedRight) * 1222u / 100u);

        if (Copy_u8SpeedLeft < 100u)
        {
            MTIMERS_vSetCompareMatch(TIM_1_A, L_u16PreloadA);
        }
        else
        {
            MTIMERS_vSetCompareMatch(TIM_1_A, 0u);
        }

        if (Copy_u8SpeedRight < 100u)
        {
            MTIMERS_vSetCompareMatch(TIM_1_B, L_u16PreloadB);
        }
        else
        {
            MTIMERS_vSetCompareMatch(TIM_1_B, 0u);
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
