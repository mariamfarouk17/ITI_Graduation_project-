#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TMR_int.h"
#include "TMR_prv.h"
#include "TMR_cfg.h"


/* ================= CALLBACKS ================= */

static void (*G_TIMER_OVF_CB)(void) = NULL;
static void (*G_TIMER_CTC_CB)(void) = NULL;
static void (*G_TIMER_ICU_CB)(void) = NULL;


/* ================= GLOBAL VARIABLES ================= */

static u8  G_u8Timer0Preload = 0;
static u8  G_u8Timer2Preload = 0;

static u32 G_u32IntervalCount = 0;


/* =========================================================
 *                       INIT
 * ========================================================= */

void MTIMERS_vInit(void)
{
    /* ================= TIMER 0 ================= */

#if TIMER0_STATE == ENABLE

    /* Fast PWM */
#if TIMER0_MODE == FAST_PWM

    SET_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, WGM01);

    /* Non-Inverting PWM */
#if PWM_OUTPUT_MODE == NON_INVERTING

    SET_BIT(TCCR0, COM01);
    CLR_BIT(TCCR0, COM00);

#elif PWM_OUTPUT_MODE == INVERTING

    SET_BIT(TCCR0, COM01);
    SET_BIT(TCCR0, COM00);

#elif PWM_OUTPUT_MODE == DISCONNECTED

    CLR_BIT(TCCR0, COM01);
    CLR_BIT(TCCR0, COM00);

#endif


#elif TIMER0_MODE == CTC

    CLR_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, WGM01);


#elif TIMER0_MODE == PWM_PHASE_CORRECT

    SET_BIT(TCCR0, WGM00);
    CLR_BIT(TCCR0, WGM01);


#elif TIMER0_MODE == NORMAL_OVERFLOW

    CLR_BIT(TCCR0, WGM00);
    CLR_BIT(TCCR0, WGM01);

#endif

#endif


    /* ================= TIMER 1 ================= */

#if TIMER1_STATE == ENABLE

#if TIMER1_MODE == ICU

    /*
     * Normal mode
     *
     * WGM13 = 0
     * WGM12 = 0
     * WGM11 = 0
     * WGM10 = 0
     */

    CLR_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);

    CLR_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);

    /*
     * ICU noise canceler disabled
     */
    CLR_BIT(TCCR1B, ICNC1);

#endif

#endif


    /* ================= TIMER 2 ================= */

#if TIMER2_STATE == ENABLE

#if TIMER2_MODE == FAST_PWM

    SET_BIT(TCCR2, WGM20);
    SET_BIT(TCCR2, WGM21);


#if PWM_OUTPUT_MODE == NON_INVERTING

    SET_BIT(TCCR2, COM21);
    CLR_BIT(TCCR2, COM20);

#elif PWM_OUTPUT_MODE == INVERTING

    SET_BIT(TCCR2, COM21);
    SET_BIT(TCCR2, COM20);

#elif PWM_OUTPUT_MODE == DISCONNECTED

    CLR_BIT(TCCR2, COM21);
    CLR_BIT(TCCR2, COM20);

#endif


#elif TIMER2_MODE == CTC

    CLR_BIT(TCCR2, WGM20);
    SET_BIT(TCCR2, WGM21);


#elif TIMER2_MODE == PWM_PHASE_CORRECT

    SET_BIT(TCCR2, WGM20);
    CLR_BIT(TCCR2, WGM21);


#elif TIMER2_MODE == NORMAL_OVERFLOW

    CLR_BIT(TCCR2, WGM20);
    CLR_BIT(TCCR2, WGM21);

#endif

#endif


    /* ================= INTERRUPTS ================= */

#if INTERRUPT_CONTROL == ENABLE

#if TIMER0_STATE == ENABLE
    MTIMERS_vEnableInterrupt(TIM_0, TIMER0_MODE);
#endif

#if TIMER1_STATE == ENABLE
    MTIMERS_vEnableInterrupt(TIM_1, TIMER1_MODE);
#endif

#if TIMER2_STATE == ENABLE
    MTIMERS_vEnableInterrupt(TIM_2, TIMER2_MODE);
#endif

#endif


    /*
     * Important:
     * Don't start timers here.
     * They are started using MTIMERS_vStartTimer().
     */
}




void MTIMERS_vStartTimer(u8 A_u8TimerID)
{
    switch(A_u8TimerID)
    {
        case TIM_0:

            TCCR0 = (TCCR0 & 0xF8)
                  | (CLK_SELECT_PRESCALER_TIM0 & 0x07);

            break;


        case TIM_1:

            TCCR1B = (TCCR1B & 0xF8)
                   | (CLK_SELECT_PRESCALER_TIM1 & 0x07);

            break;


        case TIM_2:

            TCCR2 = (TCCR2 & 0xF8)
                  | (CLK_SELECT_PRESCALER_TIM2 & 0x07);

            break;
    }
}



void MTIMERS_vStopTimer(u8 A_u8TimerID)
{
    switch(A_u8TimerID)
    {
        case TIM_0:

            TCCR0 &= 0xF8;

            break;


        case TIM_1:

            TCCR1B &= 0xF8;

            break;


        case TIM_2:

            TCCR2 &= 0xF8;

            break;
    }
}





void MTIMERS_vSetPreloadValue(
        u8 A_u8TimerID,
        u16 A_u16Preload)
{
    switch(A_u8TimerID)
    {
        case TIM_0:

            TCNT0 = (u8)A_u16Preload;
            G_u8Timer0Preload = (u8)A_u16Preload;

            break;


        case TIM_1:

            TCNT1 = A_u16Preload;

            break;


        case TIM_2:

            TCNT2 = (u8)A_u16Preload;
            G_u8Timer2Preload = (u8)A_u16Preload;

            break;
    }
}




void MTIMERS_vSetCompareMatch(
        u8 A_u8TimerID,
        u16 A_u16OCR_val)
{
    switch(A_u8TimerID)
    {
        case TIM_0:

            OCR0 = (u8)A_u16OCR_val;

            break;


        case TIM_1_A:

            OCR1A = A_u16OCR_val;

            break;


        case TIM_2:

            OCR2 = (u8)A_u16OCR_val;

            break;
    }
}




void MTIMERS_vSetTrigger(u8 A_u8TriggerType)
{
    switch(A_u8TriggerType)
    {
        case TRIG_TYPE_FALLING:

            CLR_BIT(TCCR1B, ICES1);

            break;


        case TRIG_TYPE_RISING:

            SET_BIT(TCCR1B, ICES1);

            break;
    }
}






u16 MTIMERS_u16GetCapturedValue(void)
{
    return ICR1;
}



void MTIMERS_vSetICU_CB(void (*Fptr)(void))
{
    G_TIMER_ICU_CB = Fptr;
}




void MTIMERS_vEnableInterrupt(
        u8 A_u8TimerID,
        u8 A_u8TimerMode)
{
    if(A_u8TimerID == TIM_0)
    {
        switch(A_u8TimerMode)
        {
            case NORMAL_OVERFLOW:

                SET_BIT(TIMSK, 0);

                break;


            case CTC:

                SET_BIT(TIMSK, 1);

                break;
        }
    }


    else if(A_u8TimerID == TIM_1)
    {
        if(A_u8TimerMode == ICU)
        {
            SET_BIT(TIMSK, 5);
        }
    }


    else if(A_u8TimerID == TIM_2)
    {
        switch(A_u8TimerMode)
        {
            case NORMAL_OVERFLOW:

                SET_BIT(TIMSK, 6);

                break;


            case CTC:

                SET_BIT(TIMSK, 7);

                break;
        }
    }
}






void MTIMERS_vDisableInterrupt(
        u8 A_u8TimerID,
        u8 A_u8TimerMode)
{
    if(A_u8TimerID == TIM_0)
    {
        switch(A_u8TimerMode)
        {
            case NORMAL_OVERFLOW:

                CLR_BIT(TIMSK, 0);

                break;


            case CTC:

                CLR_BIT(TIMSK, 1);

                break;
        }
    }


    else if(A_u8TimerID == TIM_1)
    {
        if(A_u8TimerMode == ICU)
        {
            CLR_BIT(TIMSK, 5);
        }
    }


    else if(A_u8TimerID == TIM_2)
    {
        switch(A_u8TimerMode)
        {
            case NORMAL_OVERFLOW:

                CLR_BIT(TIMSK, 6);

                break;


            case CTC:

                CLR_BIT(TIMSK, 7);

                break;
        }
    }
}





void MTIMERS_vSetInterval_CTC(
        void (*Fptr)(void),
        u32 A_u32IntervalCount)
{
    G_u32IntervalCount = A_u32IntervalCount;
    G_TIMER_CTC_CB = Fptr;
}




void MTIMERS_vSetInterval_OVF(
        void (*Fptr)(void),
        u32 A_u32IntervalCount)
{
    G_u32IntervalCount = A_u32IntervalCount;
    G_TIMER_OVF_CB = Fptr;
}