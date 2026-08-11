#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../TMR/TMR_int.h"

#include "PWM_int.h"
#include "PWM_prv.h"
#include "PWM_cfg.h"


/* =========================================================
 *                      PWM Configure
 * ========================================================= */

void PWM_Configure(
        PWM_ENUM_PWMs Copy_PWM,
        PWM_ENUM_Prescalers Copy_Prescaler,
        PWM_ENUM_WaveGenerationModes Copy_WaveGenerationMode,
        u16 Copy_TopValue)
{
    switch(Copy_PWM)
    {

        /* ================= TIMER0 ================= */

        case PWM_PWM0:

            /*
             * Fast PWM
             *
             * WGM01 = 1
             * WGM00 = 1
             */

            if(Copy_WaveGenerationMode == PWM_WGM_FAST_PWM0)
            {
                SET_BIT(PWM_TCCR0, PWM_TCCR0_WGM00);
                SET_BIT(PWM_TCCR0, PWM_TCCR0_WGM01);
            }


            /*
             * Phase Correct PWM
             */

            else if(Copy_WaveGenerationMode ==
                    PWM_WGM_PHASE_CORRECT_PWM0)
            {
                SET_BIT(PWM_TCCR0, PWM_TCCR0_WGM00);
                CLR_BIT(PWM_TCCR0, PWM_TCCR0_WGM01);
            }


            /*
             * Timer0 is 8-bit.
             * Therefore TOP = 255.
             *
             * Copy_TopValue is not used here.
             */

            break;


        /* ================= TIMER2 ================= */

        case PWM_PWM2:

            /*
             * Fast PWM
             *
             * WGM21 = 1
             * WGM20 = 1
             */

            if(Copy_WaveGenerationMode == PWM_WGM_FAST_PWM2)
            {
                SET_BIT(PWM_TCCR2, PWM_TCCR2_WGM20);
                SET_BIT(PWM_TCCR2, PWM_TCCR2_WGM21);
            }


            /*
             * Phase Correct PWM
             */

            else if(Copy_WaveGenerationMode ==
                    PWM_WGM_PHASE_CORRECT_PWM2)
            {
                SET_BIT(PWM_TCCR2, PWM_TCCR2_WGM20);
                CLR_BIT(PWM_TCCR2, PWM_TCCR2_WGM21);
            }


            /*
             * Timer2 is 8-bit.
             * TOP = 255.
             */

            break;


        default:
            break;
    }
}





void PWM_ConfigurePin(
        PWM_ENUM_Pins Copy_Pin,
        PWM_ENUM_PinModes Copy_PinMode,
        u16 Copy_DutyValue)
{
    u8 Local_u8OCRValue;


    /*
     * Convert Duty Percentage
     *
     * Copy_DutyValue:
     *
     * 0   -> 0%
     * 50  -> 50%
     * 100 -> 100%
     *
     * OCR = Duty * 255 / 100
     */

    if(Copy_DutyValue > 100)
    {
        Copy_DutyValue = 100;
    }


    Local_u8OCRValue =
            ((u32)Copy_DutyValue * 255) / 100;


    switch(Copy_Pin)
    {

        /* ================= OC0 ================= */

        case PWM_PIN_OC0:

            if(Copy_PinMode == PWM_PIN_MODE_NON_INVERTING)
            {
                /*
                 * COM01 = 1
                 * COM00 = 0
                 */

                SET_BIT(PWM_TCCR0, PWM_TCCR0_COM01);
                CLR_BIT(PWM_TCCR0, PWM_TCCR0_COM00);
            }


            else if(Copy_PinMode == PWM_PIN_MODE_INVERTING)
            {
                /*
                 * COM01 = 1
                 * COM00 = 1
                 */

                SET_BIT(PWM_TCCR0, PWM_TCCR0_COM01);
                SET_BIT(PWM_TCCR0, PWM_TCCR0_COM00);
            }


            else
            {
                /*
                 * Disconnect OC0
                 */

                CLR_BIT(PWM_TCCR0, PWM_TCCR0_COM01);
                CLR_BIT(PWM_TCCR0, PWM_TCCR0_COM00);
            }


            PWM_OCR0 = Local_u8OCRValue;

            break;


        /* ================= OC2 ================= */

        case PWM_PIN_OC2:

            if(Copy_PinMode == PWM_PIN_MODE_NON_INVERTING)
            {
                /*
                 * COM21 = 1
                 * COM20 = 0
                 */

                SET_BIT(PWM_TCCR2, PWM_TCCR2_COM21);
                CLR_BIT(PWM_TCCR2, PWM_TCCR2_COM20);
            }


            else if(Copy_PinMode == PWM_PIN_MODE_INVERTING)
            {
                /*
                 * COM21 = 1
                 * COM20 = 1
                 */

                SET_BIT(PWM_TCCR2, PWM_TCCR2_COM21);
                SET_BIT(PWM_TCCR2, PWM_TCCR2_COM20);
            }


            else
            {
                /*
                 * Disconnect OC2
                 */

                CLR_BIT(PWM_TCCR2, PWM_TCCR2_COM21);
                CLR_BIT(PWM_TCCR2, PWM_TCCR2_COM20);
            }


            PWM_OCR2 = Local_u8OCRValue;

            break;


        default:
            break;
    }
}




void PWM_StartPWM(PWM_ENUM_PWMs Copy_PWM)
{
    switch(Copy_PWM)
    {
        case PWM_PWM0:

            MTIMERS_vStartTimer(TIM_0);

            break;


        case PWM_PWM2:

            MTIMERS_vStartTimer(TIM_2);

            break;


        default:
            break;
    }
}




void PWM_StopPWM(PWM_ENUM_PWMs Copy_PWM)
{
    switch(Copy_PWM)
    {
        case PWM_PWM0:

            MTIMERS_vStopTimer(TIM_0);

            break;


        case PWM_PWM2:

            MTIMERS_vStopTimer(TIM_2);

            break;


        default:
            break;
    }
}








