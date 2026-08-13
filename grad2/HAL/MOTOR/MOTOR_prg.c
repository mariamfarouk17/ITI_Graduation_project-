/*
 * MOTOR_prg.c
 *
 *  Created on: Aug 11, 2026
 *      Author: HP
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/TIMER/TIMER_int.h"

#include "MOTOR_int.h"
#include "MOTOR_cfg.h"


void HMOTOR_vINIT(void)
{
    // Direction pins
    MDIO_vSetPinDir(MOTOR1_IN1_PORT, MOTOR1_IN1_PIN, DIO_OUTPUT);

    MDIO_vSetPinDir(MOTOR1_IN2_PORT, MOTOR1_IN2_PIN, DIO_OUTPUT);


    MDIO_vSetPinDir(MOTOR2_IN1_PORT, MOTOR2_IN1_PIN, DIO_OUTPUT);

    MDIO_vSetPinDir(MOTOR2_IN2_PORT, MOTOR2_IN2_PIN, DIO_OUTPUT);

    /* PWM pins */

        MDIO_vSetPinDir(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);

        MDIO_vSetPinDir(DIO_PORTD, DIO_PIN7, DIO_OUTPUT);


    // Start PWM Timers
    MTIMER_vSetCompareMatch(TIMER_0, 0);
    MTIMER_vSetCompareMatch(TIMER_2, 0);

    MTIMER_vStartTimer(TIMER_0);
    MTIMER_vStartTimer(TIMER_2);
}


void HMOTOR_vSetSpeed(u8 A_u8MotorID, u8 A_u8Speed)
{
    u8 L_u8OCRValue;

    if(A_u8Speed > 100)
    {
        A_u8Speed = 100;
    }

    L_u8OCRValue = ((u16)A_u8Speed * 255) / 100;


    if(A_u8MotorID == MOTOR_1)
    {
        MTIMER_vSetCompareMatch(TIMER_0, L_u8OCRValue);
    }

    else if(A_u8MotorID == MOTOR_2)
    {
        MTIMER_vSetCompareMatch(TIMER_2,  L_u8OCRValue);
    }
}


void HMOTOR_vSetDirection(u8 A_u8MotorID,
                          u8 A_u8Direction)
{
    if(A_u8MotorID == MOTOR_1)
    {
        switch(A_u8Direction)
        {
            case MOTOR_FORWARD:

                MDIO_vSetPinVal(MOTOR1_IN1_PORT,
                                 MOTOR1_IN1_PIN,
                                 DIO_LOW);

                MDIO_vSetPinVal(MOTOR1_IN2_PORT,
                                 MOTOR1_IN2_PIN,
                                 DIO_HIGH);

                break;


            case MOTOR_BACKWARD:

                MDIO_vSetPinVal(MOTOR1_IN1_PORT,
                                 MOTOR1_IN1_PIN,
                                 DIO_HIGH);

                MDIO_vSetPinVal(MOTOR1_IN2_PORT,
                                 MOTOR1_IN2_PIN,
                                 DIO_LOW);

                break;


            case MOTOR_STOP:

                MDIO_vSetPinVal(MOTOR1_IN1_PORT,
                                 MOTOR1_IN1_PIN,
                                 DIO_LOW);

                MDIO_vSetPinVal(MOTOR1_IN2_PORT,
                                 MOTOR1_IN2_PIN,
                                 DIO_LOW);

                break;
        }
    }


    else if(A_u8MotorID == MOTOR_2)
    {
        switch(A_u8Direction)
        {
            case MOTOR_FORWARD:

                MDIO_vSetPinVal(MOTOR2_IN1_PORT, MOTOR2_IN1_PIN, DIO_LOW);

                MDIO_vSetPinVal(MOTOR2_IN2_PORT, MOTOR2_IN2_PIN, DIO_HIGH);

                break;


            case MOTOR_BACKWARD:

                MDIO_vSetPinVal(MOTOR2_IN1_PORT, MOTOR2_IN1_PIN, DIO_HIGH);

                MDIO_vSetPinVal(MOTOR2_IN2_PORT, MOTOR2_IN2_PIN, DIO_LOW);

                break;


            case MOTOR_STOP:

                MDIO_vSetPinVal(MOTOR2_IN1_PORT, MOTOR2_IN1_PIN, DIO_LOW);

                MDIO_vSetPinVal(MOTOR2_IN2_PORT, MOTOR2_IN2_PIN, DIO_LOW);

                break;
        }
    }
}

void HMOTOR_vStop(u8 A_u8MotorID)
{
    HMOTOR_vSetDirection(A_u8MotorID, MOTOR_STOP);

    HMOTOR_vSetSpeed(A_u8MotorID, 0);
}
