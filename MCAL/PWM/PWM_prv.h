#ifndef MCAL_PWM_PWM_PRV_H_
#define MCAL_PWM_PWM_PRV_H_

#include "../../LIB/STD_TYPES.h"


/* ================= TIMER0 ================= */

#define PWM_TCCR0    *((volatile u8*)0x53)
#define PWM_OCR0     *((volatile u8*)0x5C)


/* ================= TIMER2 ================= */

#define PWM_TCCR2    *((volatile u8*)0x45)
#define PWM_OCR2     *((volatile u8*)0x43)


/* ================= TIMER0 BITS ================= */

#define PWM_TCCR0_FOC0    7
#define PWM_TCCR0_WGM00   6
#define PWM_TCCR0_COM01   5
#define PWM_TCCR0_COM00   4
#define PWM_TCCR0_WGM01   3
#define PWM_TCCR0_CS02    2
#define PWM_TCCR0_CS01    1
#define PWM_TCCR0_CS00    0


/* ================= TIMER2 BITS ================= */

#define PWM_TCCR2_FOC2    7
#define PWM_TCCR2_WGM20   6
#define PWM_TCCR2_COM21   5
#define PWM_TCCR2_COM20   4
#define PWM_TCCR2_WGM21   3
#define PWM_TCCR2_CS22    2
#define PWM_TCCR2_CS21    1
#define PWM_TCCR2_CS20    0


/* ================= TIMER MODES ================= */

#define PWM_FAST_PWM       0
#define PWM_PHASE_CORRECT  1


/* ================= PRESCALERS ================= */

#define PWM_NO_CLK              0
#define PWM_PRESCALER_1_VALUE   1
#define PWM_PRESCALER_8_VALUE   2
#define PWM_PRESCALER_64_VALUE  3
#define PWM_PRESCALER_256_VALUE 4
#define PWM_PRESCALER_1024_VALUE 5


#endif /* MCAL_PWM_PWM_PRV_H_ */