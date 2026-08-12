/*
 * ULTRASONIC_prg.c
 *
 *  Created on: 11 Aug 2026
 *      Author: LOQ
 */


#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/EXT_INT/EXTI_int.h"
#include "../../MCAL/TIMER/TMR_int.h"

#include <util/delay.h>

#include "ULTRASONIC_int.h"
#include "ULTRASONIC_cfg.h"

/* -------------------------------------------------- */
/*                  Global Variables                  */
/* -------------------------------------------------- */

static volatile u8  G_u8EchoState = 0;
static volatile u8  G_u8MeasurementReady = 0;
static volatile u32 G_u32EchoTime = 0;

/* -------------------------------------------------- */
/*               Ultrasonic Trigger                   */
/* -------------------------------------------------- */

static void HULTRASONIC_vTrigger(void)
{
    // Fix: Used ULTRASONIC_TRIGGER_PORT instead of ULTRASONIC_ECHO_PORT
    MDIO_vSetPinVal(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, DIO_HIGH);
    _delay_us(10);
    MDIO_vSetPinVal(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, DIO_LOW);
}

/* -------------------------------------------------- */
/*               Echo Callback                        */
/* -------------------------------------------------- */

static void HULTRASONIC_vEchoCallback(void)
{
    u16 Local_u16TimerValue;
    u16 Local_u16OverflowCount;

    /* First interrupt: Echo pin transitioned LOW -> HIGH */
    if(G_u8EchoState == 0)
    {
        MTIMERS_vStopTimer(TIM_2);
        MTIMERS_vSetPreloadValue(TIM_2, 0);
        MTIMERS_vResetOverflowCount(TIM_2);
        MTIMERS_vStartTimer(TIM_2);

        /* Configure next interrupt for Falling Edge */
        MEXTI_vSetSenseControl(EXTI_INT1_ID, EXTI_FALLING);
        G_u8EchoState = 1;
    }
    /* Second interrupt: Echo pin transitioned HIGH -> LOW */
    else
    {
        MTIMERS_vStopTimer(TIM_2);

        Local_u16TimerValue     = MTIMERS_u16GetTimerValue(TIM_2);
        Local_u16OverflowCount  = MTIMERS_u16GetOverflowCount(TIM_2);

        /* Time calculation in microseconds (at 1 tick = 1us) */
        G_u32EchoTime = ((u32)Local_u16OverflowCount * 256UL) + Local_u16TimerValue;

        G_u8MeasurementReady = 1;

        /* Reset EXTI to listen for Rising Edge on next trigger */
        MEXTI_vSetSenseControl(EXTI_INT1_ID, EXTI_RISING);
        G_u8EchoState = 0;
    }
}

/* -------------------------------------------------- */
/*                    Init                            */
/* -------------------------------------------------- */

void HULTRASONIC_vInit(void)
{
    /* Trigger pin setup */
    MDIO_vSetPinDir(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, DIO_OUTPUT);
    MDIO_vSetPinVal(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, DIO_LOW);

    /* Echo pin setup */
    MDIO_vSetPinDir(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, DIO_INPUT);

    /* EXTI configuration */
    MEXTI_vSetSenseControl(EXTI_INT1_ID, EXTI_RISING);
    MEXTI_vCallBackFunction(HULTRASONIC_vEchoCallback, EXTI_INT1_ID);
    
    /* Enable EXTI INT1 */
    MEXTI_vEnableInterrupt(EXTI_INT1_ID); 
}

/* -------------------------------------------------- */
/*                Get Distance                        */
/* -------------------------------------------------- */

u16 HULTRASONIC_u16GetDistance(void)
{
    u32 Local_u32TimeoutCounter = 0;

    G_u8MeasurementReady = 0;
    G_u8EchoState = 0;

    /* Ensure EXTI looks for Rising Edge prior to triggering */
    MEXTI_vSetSenseControl(EXTI_INT1_ID, EXTI_RISING);

    /* Send Trigger pulse */
    HULTRASONIC_vTrigger();

    /* Wait for echo with a safety timeout (~30 ms max wait time) */
    while((G_u8MeasurementReady == 0) && (Local_u32TimeoutCounter < 30000UL))
    {
        Local_u32TimeoutCounter++;
        _delay_us(1);
    }

    /* Return valid distance in cm, or 0 if measurement timed out */
    if(G_u8MeasurementReady == 1)
    {
        return (u16)(G_u32EchoTime / 58UL);
    }
    else
    {
        /* Reset state if timed out */
        G_u8EchoState = 0;
        return 0; // Return 0 to indicate out-of-range or timeout
    }
}


