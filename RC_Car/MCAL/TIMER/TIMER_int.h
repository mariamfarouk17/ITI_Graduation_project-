/*
 * TIMER_int.h
 *
 *  Created on: Aug 4, 2026
 *      Author: HP
 */

#ifndef MCAL_TIMER_TIMER_INT_H_
#define MCAL_TIMER_TIMER_INT_H_

#define TIMER_0	    0
#define TIMER_1	    1
#define TIMER_1_A   2  // Capture
#define TIMER_2     3

#define ICU         4

#define TRIG_TYPE_RISING    0
#define TRIG_TYPE_FALLING   1

void MTIMER_vINIT(void);

void MTIMER_vStartTimer(u8 A_u8TimerID);
void MTIMER_vStopTimer(u8 A_u8TimerID);

// Overflow
void MTIMER_vSetPreloadValue(u8 A_u8TimerID , u16 A_u16Preload);
void MTIMER_vSetInterval_OVF(void (*Fptr)(void),u32 A_u32IntervalCount);


// CTC
void MTIMER_vSetCompareMatch(u8 A_u8TimerID , u16 A_u16OCR_val);
void MTIMER_vSetInterval_CTC(void (*Fptr)(void),u32 A_u32IntervalCount);

// ICU
void MTIMER_vSetTrigger(u8 A_u8TriggerType);
u16 MTIMER_u16GetCapturedValue(void);
void MTIMER_vSetICU_CB(void (*Fptr)(void));

// Interrupt
void MTIMER_vEnableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode);
void MTIMER_vDisableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode);


#endif /* MCAL_TIMER_TIMER_INT_H_ */
