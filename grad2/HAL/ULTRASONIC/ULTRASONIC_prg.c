/*
 * ULTRASONIC_prg.c
 *
 *  Created on: Aug 8, 2026
 *      Author: HP
 *
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/TIMER/TIMER_int.h"
#include "ULTRASONIC_int.h"
#include "ULTRASONIC_cfg.h"
#include <util/delay.h>

static volatile u16 G_u16T1 = 0;
static volatile u16 G_u16T2 = 0;
static volatile u8  G_u8EdgeState = 0;

static void HULTRASONIC_vIcuCallback(void)
{
    if (G_u8EdgeState == 0)
    {
        /* First Capture: Rising Edge */
        G_u16T1 = MTIMER_u16GetCapturedValue();
        MTIMER_vSetTrigger(TRIG_TYPE_FALLING);
        G_u8EdgeState = 1;
    }
    else if (G_u8EdgeState == 1)
    {
        /* Second Capture: Falling Edge */
        G_u16T2 = MTIMER_u16GetCapturedValue();
        MTIMER_vSetTrigger(TRIG_TYPE_RISING);
        G_u8EdgeState = 2; // Capture sequence finished
    }
}

void HULTRASONIC_vInit(void)
{
    /* Set Trigger Pin as Output */
    MDIO_vSetPinDir(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_OUTPUT);
    MDIO_vSetPinVal(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_LOW);

    /* Set Echo Pin (ICP1 - Pin D6) as Input */
    MDIO_vSetPinDir(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, DIO_INPUT);

    /* Register callback and enable interrupt */
    MTIMER_vSetICU_CB(HULTRASONIC_vIcuCallback);
    MTIMER_vSetTrigger(TRIG_TYPE_RISING);
    MTIMER_vEnableInterrupt(TIMER_1, ICU);
}

u16 HULTRASONIC_u16GetDistance(void)
{
    u16 L_u16Ticks = 0;
    u16 L_u16DistanceCm = 0;
    u32 L_u32Timeout = 0;
    u16 L_u16EchoWait = 0;

    G_u16T1 = 0;
    G_u16T2 = 0;
    G_u8EdgeState = 0;

    /* Make sure any previous echo is finished */
    while ((MDIO_u8GetPinVal(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN) == DIO_HIGH) &&
           (L_u16EchoWait < 1000))
    {
        L_u16EchoWait++;
    }

    /* Send a real 10 us pulse to the HC-SR04 trigger pin */
    MDIO_vSetPinVal(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_LOW);
    _delay_us(2);
    MDIO_vSetPinVal(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_HIGH);
    _delay_us(10);
    MDIO_vSetPinVal(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_LOW);

    /* Wait for capture sequence to complete with a safety timeout */
    while ((G_u8EdgeState != 2) && (L_u32Timeout < 60000))
    {
        L_u32Timeout++;
    }

    if (G_u8EdgeState == 2)
    {
        if (G_u16T2 >= G_u16T1)
        {
            L_u16Ticks = G_u16T2 - G_u16T1;
        }
        else
        {
            /* Timer overflow handling */
            L_u16Ticks = (65535 - G_u16T1) + G_u16T2;
        }

        /* Distance formula for 8MHz MCU with Prescaler = 8 (1us tick time) */
        if (L_u16Ticks > 0)
        {
            L_u16DistanceCm = L_u16Ticks / 58;
        }
    }

    return L_u16DistanceCm;
}
