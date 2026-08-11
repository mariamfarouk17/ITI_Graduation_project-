#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO_INT.h"
#include "EXTI_int.h"
#include "EXTI_prv.h"
#include "../../LIB/BIT_MATH.h"


static void (*G_EXTI_Callback[3])(void) = {NULL};





void MEXTI_vInit(void)
{
#if EXTI_INT0_STATE == ENABLE
    MEXTI_vSetSenseControl(
        EXTI_INT0_ID,
        EXTI_INT0_SENSE_CTRL
    );

    SET_BIT(GICR, INT0);
#endif


#if EXTI_INT1_STATE == ENABLE
    MEXTI_vSetSenseControl(
        EXTI_INT1_ID,
        EXTI_INT1_SENSE_CTRL
    );

    SET_BIT(GICR, INT1);
#endif


#if EXTI_INT2_STATE == ENABLE
    MEXTI_vSetSenseControl(
        EXTI_INT2_ID,
        EXTI_INT2_SENSE_CTRL
    );

    SET_BIT(GICR, INT2);
#endif
}

void MEXTI_vCallBackFunction(void(*Fptr)(void) , u8 A_u8InterruptNo)
{
	G_EXTI_Callback[A_u8InterruptNo] = Fptr;
}

void __vector_1(void) __attribute__((signal));

void __vector_1(void)
{
	if(G_EXTI_Callback[EXTI_INT0_ID] != NULL)
	{
		G_EXTI_Callback[EXTI_INT0_ID]();
	}
}

void __vector_2(void) __attribute__((signal));

void __vector_2(void)
{
	if(G_EXTI_Callback[EXTI_INT1_ID] != NULL)
	{
		G_EXTI_Callback[EXTI_INT1_ID]();
	}
}


void __vector_3(void) __attribute__((signal));

void __vector_3(void)
{
	if(G_EXTI_Callback[EXTI_INT2_ID] != NULL)
	{
		G_EXTI_Callback[EXTI_INT2_ID]();
	}
}



void MEXTI_vSetSenseControl(u8 A_u8InterruptNo, u8 A_u8SenseControl)
{
    switch(A_u8InterruptNo)
    {
        case EXTI_INT0_ID:

            switch(A_u8SenseControl)
            {
                case EXTI_LOW_LVL:
                    CLR_BIT(MCUCR, ISC00);
                    CLR_BIT(MCUCR, ISC01);
                    break;

                case EXTI_ONCHANGE:
                    SET_BIT(MCUCR, ISC00);
                    CLR_BIT(MCUCR, ISC01);
                    break;

                case EXTI_FALLING:
                    CLR_BIT(MCUCR, ISC00);
                    SET_BIT(MCUCR, ISC01);
                    break;

                case EXTI_RISING:
                    SET_BIT(MCUCR, ISC00);
                    SET_BIT(MCUCR, ISC01);
                    break;
            }

            break;


        case EXTI_INT1_ID:

            switch(A_u8SenseControl)
            {
                case EXTI_LOW_LVL:
                    CLR_BIT(MCUCR, ISC10);
                    CLR_BIT(MCUCR, ISC11);
                    break;

                case EXTI_ONCHANGE:
                    SET_BIT(MCUCR, ISC10);
                    CLR_BIT(MCUCR, ISC11);
                    break;

                case EXTI_FALLING:
                    CLR_BIT(MCUCR, ISC10);
                    SET_BIT(MCUCR, ISC11);
                    break;

                case EXTI_RISING:
                    SET_BIT(MCUCR, ISC10);
                    SET_BIT(MCUCR, ISC11);
                    break;
            }

            break;


        case EXTI_INT2_ID:

            switch(A_u8SenseControl)
            {
                case EXTI_FALLING:
                    CLR_BIT(MCUCSR, ISC2);
                    break;

                case EXTI_RISING:
                    SET_BIT(MCUCSR, ISC2);
                    break;
            }

            break;
    }
}
