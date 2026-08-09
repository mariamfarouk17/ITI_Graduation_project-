#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_int.h"
#include "ADC_prv.h"

void MADC_vInit(void)
{
    /*
     * Voltage Reference:
     * AVCC with external capacitor at AREF
     *
     * REFS1:REFS0 = 01
     */
    CLR_BIT(ADMUX, 7);
    SET_BIT(ADMUX, 6);

    /*
     * Right adjustment
     * ADLAR = 0
     */
    CLR_BIT(ADMUX, 5);

    /*
     * ADC Prescaler = 64
     * ADPS2:ADPS0 = 110
     */
    SET_BIT(ADCSRA, 2);
    SET_BIT(ADCSRA, 1);
    CLR_BIT(ADCSRA, 0);

    /*
     * Free Running / Auto Trigger disabled
     */
    CLR_BIT(ADCSRA, 5);

    /*
     * ADC Interrupt disabled
     */
    CLR_BIT(ADCSRA, 3);

    /*
     * Clear ADC flag
     */
    SET_BIT(ADCSRA, 4);

    /*
     * Enable ADC
     */
    SET_BIT(ADCSRA, 7);
}


u16 MADC_u16AnalogRead(u8 A_u8Channel)
{
    /*
     * Make sure channel is between 0 and 7
     */
    A_u8Channel &= 0x07;

    /*
     * Keep REFS1, REFS0 and ADLAR.
     * Change only MUX4:MUX0.
     *
     * For ATmega32 only ADC0-ADC7 are used.
     */
    ADMUX = (ADMUX & 0xE0) | A_u8Channel;

    /*
     * Start ADC conversion
     */
    SET_BIT(ADCSRA, 6);

    /*
     * Wait until conversion is complete
     */
    while (GET_BIT(ADCSRA, 4) == 0)
    {
        /* Wait */
    }

    /*
     * Clear ADC interrupt flag
     */
    SET_BIT(ADCSRA, 4);

    /*
     * Return 10-bit ADC result
     */
    return ADC;
}