#ifndef MCAL_TMR_TMR_PRV_H_
#define MCAL_TMR_TMR_PRV_H_

/* ================= TIMER 0 ================= */

#define OCR0   *((volatile u8*)(0x5C))
#define TCCR0  *((volatile u8*)(0x53))
#define TCNT0  *((volatile u8*)(0x52))


/* ================= TIMER 1 ================= */

#define TCCR1A *((volatile u8*)(0x4F))
#define TCCR1B *((volatile u8*)(0x4E))

#define TCNT1  *((volatile u16*)(0x4C))
#define OCR1A  *((volatile u16*)(0x4A))
#define OCR1B  *((volatile u16*)(0x48))
#define ICR1   *((volatile u16*)(0x46))


/* ================= TIMER 2 ================= */

#define OCR2   *((volatile u8*)(0x43))
#define TCCR2  *((volatile u8*)(0x45))
#define TCNT2  *((volatile u8*)(0x44))


/* ================= INTERRUPTS ================= */

#define TIMSK  *((volatile u8*)(0x59))
#define TIFR   *((volatile u8*)(0x58))


/* ================= TIMER 0 BITS ================= */

#define FOC0   7
#define WGM00  6
#define COM01  5
#define COM00  4
#define WGM01  3
#define CS02   2
#define CS01   1
#define CS00   0


/* ================= TIMER 1 BITS ================= */

#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define FOC1A  3
#define FOC1B  2
#define WGM11  1
#define WGM10  0

#define ICNC1  7
#define ICES1  6
#define WGM13  4
#define WGM12  3
#define CS12   2
#define CS11   1
#define CS10   0


/* ================= TIMER 2 BITS ================= */

#define FOC2   7
#define WGM20  6
#define COM21  5
#define COM20  4
#define WGM21  3
#define CS22   2
#define CS21   1
#define CS20   0


/* ================= MODES ================= */

#define NORMAL_OVERFLOW      0
#define CTC                  1
#define PWM_PHASE_CORRECT   2
#define FAST_PWM             3


/* ================= PRESCALER ================= */

#define NO_CLK               0x00
#define CLK_NO_PRESCALLING   0x01
#define CLK_8                0x02
#define CLK_64               0x03
#define CLK_256              0x04
#define CLK_1024             0x05

#define EXTERNAL_TO_FALLING  0x06
#define EXTERNAL_TO_RISING   0x07


#define ENABLE  1
#define DISABLE 0

#endif
