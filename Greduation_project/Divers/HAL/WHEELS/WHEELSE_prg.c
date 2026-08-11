#include "WHEELS_cfg.h"
#include "WHEELS_int.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/PWM/PWM_int.h"


void WHEELS_Init(u8 Copy_InitialSpeed)
{
    /*
     * Configure PWM for LEFT motor
     * Timer0 -> OC0
     */

    PWM_Configure(
        PWM_PWM0,
        PWM_PRESCALER_8,
        PWM_WGM_FAST_PWM0,
        255
    );


    /*
     * Configure PWM for RIGHT motor
     * Timer2 -> OC2
     */

    PWM_Configure(
        PWM_PWM2,
        PWM_PRESCALER_8,
        PWM_WGM_FAST_PWM2,
        255
    );


    /*
     * Configure LEFT motor speed
     */

    PWM_ConfigurePin(
        WHEELS_LEFT_SPEED_PIN,
        PWM_PIN_MODE_NON_INVERTING,
        Copy_InitialSpeed
    );


    /*
     * Configure RIGHT motor speed
     */

    PWM_ConfigurePin(
        WHEELS_RIGHT_SPEED_PIN,
        PWM_PIN_MODE_NON_INVERTING,
        Copy_InitialSpeed
    );


    /*
     * Start LEFT motor PWM
     */

    PWM_StartPWM(PWM_PWM0);


    /*
     * Start RIGHT motor PWM
     */

    PWM_StartPWM(PWM_PWM2);
}




void WHEELS_Move(WHEELS_ENUM_Directions Copy_Direction)
{
    switch(Copy_Direction)
    {
        case WHEELS_DIRECTION_FORWARD:

            /* Left Forward */

            DIO_SetPinValue(
                WHEELS_LEFT_DIRECTION_PORT,
                WHEELS_LEFT_POSITIVE_PIN,
                DIO_HIGH
            );

            DIO_SetPinValue(
                WHEELS_LEFT_DIRECTION_PORT,
                WHEELS_LEFT_NEGATIVE_PIN,
                DIO_LOW
            );


            /* Right Forward */

            DIO_SetPinValue(
                WHEELS_RIGHT_DIRECTION_PORT,
                WHEELS_RIGHT_POSITIVE_PIN,
                DIO_HIGH
            );

            DIO_SetPinValue(
                WHEELS_RIGHT_DIRECTION_PORT,
                WHEELS_RIGHT_NEGATIVE_PIN,
                DIO_LOW
            );

            break;


        case WHEELS_DIRECTION_BACKWARD:

            /* Left Backward */

            DIO_SetPinValue(
                WHEELS_LEFT_DIRECTION_PORT,
                WHEELS_LEFT_POSITIVE_PIN,
                DIO_LOW
            );

            DIO_SetPinValue(
                WHEELS_LEFT_DIRECTION_PORT,
                WHEELS_LEFT_NEGATIVE_PIN,
                DIO_HIGH
            );


            /* Right Backward */

            DIO_SetPinValue(
                WHEELS_RIGHT_DIRECTION_PORT,
                WHEELS_RIGHT_POSITIVE_PIN,
                DIO_LOW
            );

            DIO_SetPinValue(
                WHEELS_RIGHT_DIRECTION_PORT,
                WHEELS_RIGHT_NEGATIVE_PIN,
                DIO_HIGH
            );

            break;


        case WHEELS_DIRECTION_LEFT:

            /* Left wheels backward */

            DIO_SetPinValue(
                WHEELS_LEFT_DIRECTION_PORT,
                WHEELS_LEFT_POSITIVE_PIN,
                DIO_LOW
            );

            DIO_SetPinValue(
                WHEELS_LEFT_DIRECTION_PORT,
                WHEELS_LEFT_NEGATIVE_PIN,
                DIO_HIGH
            );


            /* Right wheels forward */

            DIO_SetPinValue(
                WHEELS_RIGHT_DIRECTION_PORT,
                WHEELS_RIGHT_POSITIVE_PIN,
                DIO_HIGH
            );

            DIO_SetPinValue(
                WHEELS_RIGHT_DIRECTION_PORT,
                WHEELS_RIGHT_NEGATIVE_PIN,
                DIO_LOW
            );

            break;


        case WHEELS_DIRECTION_RIGHT:

            /* Left wheels forward */

            DIO_SetPinValue(
                WHEELS_LEFT_DIRECTION_PORT,
                WHEELS_LEFT_POSITIVE_PIN,
                DIO_HIGH
            );

            DIO_SetPinValue(
                WHEELS_LEFT_DIRECTION_PORT,
                WHEELS_LEFT_NEGATIVE_PIN,
                DIO_LOW
            );


            /* Right wheels backward */

            DIO_SetPinValue(
                WHEELS_RIGHT_DIRECTION_PORT,
                WHEELS_RIGHT_POSITIVE_PIN,
                DIO_LOW
            );

            DIO_SetPinValue(
                WHEELS_RIGHT_DIRECTION_PORT,
                WHEELS_RIGHT_NEGATIVE_PIN,
                DIO_HIGH
            );

            break;
    }
}




void WHEELS_SetRightSpeed(u8 Copy_Speed)
{
    PWM_ConfigurePin(
        WHEELS_RIGHT_SPEED_PIN,
        PWM_PIN_MODE_NON_INVERTING,
        Copy_Speed
    );
}



void WHEELS_SetLeftSpeed(u8 Copy_Speed)
{
    PWM_ConfigurePin(
        WHEELS_LEFT_SPEED_PIN,
        PWM_PIN_MODE_NON_INVERTING,
        Copy_Speed
    );
}


void WHEELS_SetSpeed(u8 Copy_Speed)
{
    WHEELS_SetLeftSpeed(Copy_Speed);
    WHEELS_SetRightSpeed(Copy_Speed);
}


void WHEELS_Stop(void)
{
    /* Left motor */

    DIO_SetPinValue(
        WHEELS_LEFT_DIRECTION_PORT,
        WHEELS_LEFT_POSITIVE_PIN,
        DIO_LOW
    );

    DIO_SetPinValue(
        WHEELS_LEFT_DIRECTION_PORT,
        WHEELS_LEFT_NEGATIVE_PIN,
        DIO_LOW
    );


    /* Right motor */

    DIO_SetPinValue(
        WHEELS_RIGHT_DIRECTION_PORT,
        WHEELS_RIGHT_POSITIVE_PIN,
        DIO_LOW
    );

    DIO_SetPinValue(
        WHEELS_RIGHT_DIRECTION_PORT,
        WHEELS_RIGHT_NEGATIVE_PIN,
        DIO_LOW
    );
}