#ifndef MCAL_PWM_PWM_CFG_H_
#define MCAL_PWM_PWM_CFG_H_


/* ================= PWM Configuration ================= */

/*
 * Timer0:
 * Motor Left
 */

#define PWM0_ENABLE    1

#define PWM0_PRESCALER PWM_PRESCALER_8

#define PWM0_MODE      PWM_WGM_FAST_PWM0


/*
 * Timer2:
 * Motor Right
 */

#define PWM2_ENABLE    1

#define PWM2_PRESCALER PWM_PRESCALER_8

#define PWM2_MODE      PWM_WGM_FAST_PWM2


/*
 * PWM Output Mode
 *
 * NON_INVERTING:
 * 0%   -> OCR = 0
 * 100% -> OCR = 255
 */

#define PWM_OUTPUT_MODE PWM_PIN_MODE_NON_INVERTING


#endif /* MCAL_PWM_PWM_CFG_H_ */