#ifndef MCAL_TMR_TMR_INT_H_
#define MCAL_TMR_TMR_INT_H_

#include "../../LIB/STD_TYPES.h"


#define TIM_0    0
#define TIM_1    1
#define TIM_1_A  2
#define TIM_2    3

#define ICU      4


#define TRIG_TYPE_RISING   0
#define TRIG_TYPE_FALLING  1


void MTIMERS_vInit(void);

void MTIMERS_vStartTimer(u8 A_u8TimerID);
void MTIMERS_vStopTimer(u8 A_u8TimerID);


/* Overflow */

void MTIMERS_vSetPreloadValue(
        u8 A_u8TimerID,
        u16 A_u16Preload
);

void MTIMERS_vSetInterval_OVF(
        void (*Fptr)(void),
        u32 A_u32IntervalCount
);


/* CTC */

void MTIMERS_vSetCompareMatch(
        u8 A_u8TimerID,
        u16 A_u16OCR_val
);

void MTIMERS_vSetInterval_CTC(
        void (*Fptr)(void),
        u32 A_u32IntervalCount
);


/* ICU */

void MTIMERS_vSetTrigger(u8 A_u8TriggerType);

u16 MTIMERS_u16GetCapturedValue(void);

void MTIMERS_vSetICU_CB(void (*Fptr)(void));


/* Interrupt */

void MTIMERS_vEnableInterrupt(
        u8 A_u8TimerID,
        u8 A_u8TimerMode
);

void MTIMERS_vDisableInterrupt(
        u8 A_u8TimerID,
        u8 A_u8TimerMode
);

#endif
