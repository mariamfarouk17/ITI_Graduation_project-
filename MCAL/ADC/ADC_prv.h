#ifndef MCAL_ADC_ADC_PRV_H_
#define MCAL_ADC_ADC_PRV_H_

/* ADC Registers - ATmega32 */

#define ADMUX   (*(volatile u8*)(0x27))
#define ADCSRA  (*(volatile u8*)(0x26))
#define ADCH    (*(volatile u8*)(0x25))
#define ADCL    (*(volatile u8*)(0x24))
#define SFIOR   (*(volatile u8*)(0x50))

/* 16-bit ADC result register */
#define ADC     (*(volatile u16*)(0x24))

#endif /* MCAL_ADC_ADC_PRV_H_ */