#ifndef MCAL_PWM_PWM_INT_H_
#define MCAL_PWM_PWM_INT_H_

#include "../../LIB/STD_TYPES.h"


/* ================= PWM Timers ================= */

typedef enum
{
    PWM_PWM0,
    PWM_PWM2

} PWM_ENUM_PWMs;


/* ================= Prescalers ================= */

typedef enum
{
    PWM_PRESCALER_1 = 1,
    PWM_PRESCALER_8,
    PWM_PRESCALER_64,
    PWM_PRESCALER_256,
    PWM_PRESCALER_1024

} PWM_ENUM_Prescalers;


/* ================= Wave Generation Modes ================= */

typedef enum
{
    PWM_WGM_FAST_PWM0,
    PWM_WGM_PHASE_CORRECT_PWM0,

    PWM_WGM_FAST_PWM2,
    PWM_WGM_PHASE_CORRECT_PWM2

} PWM_ENUM_WaveGenerationModes;


/* ================= PWM Pins ================= */

typedef enum
{
    PWM_PIN_OC0,
    PWM_PIN_OC2

} PWM_ENUM_Pins;


/* ================= PWM Pin Modes ================= */

typedef enum
{
    PWM_PIN_MODE_DISCONNECTED,
    PWM_PIN_MODE_NON_INVERTING,
    PWM_PIN_MODE_INVERTING

} PWM_ENUM_PinModes;


/* ================= Functions ================= */

void PWM_Configure(
        PWM_ENUM_PWMs Copy_PWM,
        PWM_ENUM_Prescalers Copy_Prescaler,
        PWM_ENUM_WaveGenerationModes Copy_WaveGenerationMode,
        u16 Copy_TopValue
);


void PWM_ConfigurePin(
        PWM_ENUM_Pins Copy_Pin,
        PWM_ENUM_PinModes Copy_PinMode,
        u16 Copy_DutyValue
);


void PWM_StartPWM(
        PWM_ENUM_PWMs Copy_PWM
);


void PWM_StopPWM(
        PWM_ENUM_PWMs Copy_PWM
);


#endif /* MCAL_PWM_PWM_INT_H_ */
