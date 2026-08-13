/*
 * TIMER_prg.c
 *
 *  Created on: Aug 4, 2026
 *      Author: HP
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/TIMER/TIMER_cfg.h"
#include "../../MCAL/TIMER/TIMER_int.h"
#include "../../MCAL/TIMER/TIMER_prv.h"

// Callback function pointer.
static void (*G_TIMER_OVF_CB)(void) = {NULL};
static void (*G_TIMER_CTC_CB)(void) = {NULL};
static void (*G_TIMER_ICU_CB)(void) = {NULL};

static u8 G_u8Time0Preload=0;
static u32 G_32IntervalCount=0;

// Initialize Timer
void MTIMER_vINIT(void)
{
	// Timer 0
#if TIMER0_STATE == ENABLE

#if TIMER0_MODE == NORMAL_OVERFLOW
	CLR_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);

#elif TIMER0_MODE == CTC
	SET_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);

#elif TIMER0_MODE == PWM_PHASE_CORRECT
	CLR_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);

	// PWM
#if	PWM_OUTPUT_MODE ==	NON_INVERTING
	SET_BIT(TCCR0,COM01);
	CLR_BIT(TCCR0,COM00);

#elif	PWM_OUTPUT_MODE ==	INVERTING
	SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0,COM00);

#elif	PWM_OUTPUT_MODE ==	DISCONNECTED
	CLR_BIT(TCCR0,COM01);
	CLR_BIT(TCCR0,COM00);

#else
#error "Wrong PWM mode"

#endif

#elif TIMER0_MODE == FAST_PWM
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);

#if	PWM_OUTPUT_MODE ==	NON_INVERTING
	SET_BIT(TCCR0,COM01);
	CLR_BIT(TCCR0,COM00);

#elif	PWM_OUTPUT_MODE ==	INVERTING
	SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0,COM00);

#elif	PWM_OUTPUT_MODE ==	DISCONNECTED
	CLR_BIT(TCCR0,COM01);
	CLR_BIT(TCCR0,COM00);

#else
#error "Wrong PWM mode"

#endif

#else
#error "Incorrect mode"

#endif

	// Enabling Interrupt
#if INTERRUPT_CONTROL == ENABLE
	MTIMER_vEnableInterrupt(TIMER_0, TIMER0_MODE);

#elif INTERRUPT_CONTROL == DISABLE
	MTIMER_vDisableInterrupt(TIMER_0, TIMER0_MODE);

#else
#error "Incorrect value"

#endif

	// STOP TIMER0
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);


#endif


#if TIMER1_STATE == ENABLE

#if TIMER1_MODE == FAST_PWM
	CLR_BIT(TCCR1A , 0);
	SET_BIT(TCCR1A , 1);
	SET_BIT(TCCR1B , 3);
	SET_BIT(TCCR1B , 4);

	// NON_INVERTING
	CLR_BIT(TCCR1A , 6);
	SET_BIT(TCCR1A , 7);

	ICR1 = 20000;

#elif TIMER1_MODE == ICU
	//Normal Mode
	CLR_BIT(TCCR1A , 0);
	CLR_BIT(TCCR1A , 1);
	CLR_BIT(TCCR1B , 3);
	CLR_BIT(TCCR1B , 4);

	CLR_BIT(TCCR1A , 6);
	CLR_BIT(TCCR1A , 7);

	// Capture Rising
	SET_BIT(TCCR1B , 6);

#endif

	// Enabling Interrupt
#if INTERRUPT_CONTROL == ENABLE
	MTIMER_vEnableInterrupt(TIMER_1, TIMER1_MODE);

#elif INTERRUPT_CONTROL == DISABLE
	MTIMER_vDisableInterrupt(TIMER_1, TIMER1_MODE);

#else
#error "Incorrect value"

#endif

	// STOP TIMER1
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);


#endif


	// Timer_2
#if TIMER2_STATE == ENABLE

#if TIMER2_MODE == NORMAL_OVERFLOW

	CLR_BIT(TCCR2, WGM21);
	CLR_BIT(TCCR2, WGM20);


#elif TIMER2_MODE == CTC

	SET_BIT(TCCR2, WGM21);
	CLR_BIT(TCCR2, WGM20);


#elif TIMER2_MODE == PWM_PHASE_CORRECT

	CLR_BIT(TCCR2, WGM21);
	SET_BIT(TCCR2, WGM20);

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


#elif TIMER2_MODE == FAST_PWM

	SET_BIT(TCCR2, WGM21);
	SET_BIT(TCCR2, WGM20);

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

#endif


	/* Stop Timer2 initially */

	CLR_BIT(TCCR2, CS20);
	CLR_BIT(TCCR2, CS21);
	CLR_BIT(TCCR2, CS22);

#endif

}

void MTIMER_vStartTimer(u8 A_u8TimerID)
{
	if (A_u8TimerID == TIMER_0)
	{
		TCCR0 = (TCCR0 & 0xF8) | (0x07 & CLK_SELECT_PRESCALER_TIM0) ;

	}

	if (A_u8TimerID == TIMER_1)
	{
		TCCR1B= (TCCR1B & 0xF8) | (0x07 & CLK_SELECT_PRESCALER_TIM1) ;

	}
	if(A_u8TimerID == TIMER_2)
	{
		TCCR2 = (TCCR2 & 0xF8) |
		            (0x07 & CLK_SELECT_PRESCALER_TIM2);
	}
}
void MTIMER_vStopTimer(u8 A_u8TimerID)
{
	if (A_u8TimerID == TIMER_0)
	{
		TCCR0 = (TCCR0 & 0xF8) | (0x07 & 0x00) ;

	}

	if (A_u8TimerID == TIMER_1)
	{
		TCCR1B = (TCCR1B & 0xF8) | (0x07 & 0x00) ;

	}

	if(A_u8TimerID == TIMER_2)
	{
	    TCCR2 = (TCCR2 & 0xF8) | (0x07 & 0x00);
	}
}

//Overflow
void MTIMER_vSetPreloadValue(u8 A_u8TimerID , u16 A_u16Preload)
{
	switch(A_u8TimerID)
	{
	case TIMER_0:
		TCNT0 = (u8)A_u16Preload;
		G_u8Time0Preload = (u8)A_u16Preload;
		break;

	case TIMER_1:
		TCNT1 = A_u16Preload;
		break;
	}
}

//CTC
void MTIMER_vSetCompareMatch(u8 A_u8TimerID , u16 A_u16OCR_val)
{
	switch(A_u8TimerID)
	{
	case TIMER_0:
		OCR0 = (u8)A_u16OCR_val;
		break;

	case TIMER_1_A:
		OCR1A = (u16)A_u16OCR_val;
		break;

	case TIMER_2:
		 OCR2 = (u8)A_u16OCR_val;
		 break;
	}
}

// ICU
void MTIMER_vSetTrigger(u8 A_u8TriggerType)
{
	switch(A_u8TriggerType)
	{
	case TRIG_TYPE_RISING :
		SET_BIT(TCCR1B , 6);
		break;

	case TRIG_TYPE_FALLING :
			CLR_BIT(TCCR1B , 6);
			break;
	}
	SET_BIT (TIFR , 5);

}

u16 MTIMER_u16GetCapturedValue(void)
{
	return ICR1;
}

void MTIMER_vSetICU_CB(void (*Fptr)(void))
{
	G_TIMER_ICU_CB = Fptr;
}

void MTIMER_vEnableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode)
{
	if(A_u8TimerID == TIMER_0)
	{
		switch(A_u8TimerMode)
		{
		case NORMAL_OVERFLOW:
			SET_BIT(TIMSK,0);
			break;

		case CTC:
			SET_BIT(TIMSK,1);
			break;
		}
	}

	if(A_u8TimerID == TIMER_1)
		{
			switch(A_u8TimerMode)
			{
			case ICU:
				SET_BIT(TIMSK,5);
				break;
			}
		}

}
void MTIMER_vDisableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode)
{

	if(A_u8TimerID == TIMER_0)
	{
		switch(A_u8TimerMode)
		{
		case NORMAL_OVERFLOW:
			CLR_BIT(TIMSK,0);
			break;

		case CTC:
			CLR_BIT(TIMSK,1);
			break;
		}
	}

	if(A_u8TimerID == TIMER_1)
			{
				switch(A_u8TimerMode)
				{
				case ICU:
					CLR_BIT(TIMSK,5);
					break;
				}
			}

}


void MTIMER_vSetInterval_CTC(void (*Fptr)(void),u32 A_u32IntervalCount)
{
	G_32IntervalCount= A_u32IntervalCount;
	G_TIMER_CTC_CB = Fptr;

}

void MTIMER_vSetInterval_OVF(void (*Fptr)(void),u32 A_u32IntervalCount)
{
	G_32IntervalCount= A_u32IntervalCount;
	G_TIMER_OVF_CB = Fptr;

}

// Timer_0 Overflow
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	//A local static unsigned 32-bit variable used to count timer overflows."
	static u32 LS_u32T_OVF = 0;


	LS_u32T_OVF++;
	if(LS_u32T_OVF == G_32IntervalCount)
	{
	    // Reload the pre-load value FOR THE NEXT INTERVAL
		TCNT0 = G_u8Time0Preload;

		if(G_TIMER_OVF_CB != NULL)
		{
			G_TIMER_OVF_CB();
		}
		LS_u32T_OVF = 0;
	}

}

//Timer_0 CTC
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static u32 LS_u32Counter = 0;
	LS_u32Counter++;
	if(LS_u32Counter == G_32IntervalCount)
	{
		if(G_TIMER_CTC_CB != NULL)
		{
			G_TIMER_CTC_CB();
		}
		LS_u32Counter = 0;
	}
}

// Timer_1 ICU
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
		if(G_TIMER_ICU_CB != NULL)
		{
			G_TIMER_ICU_CB();
		}
}


