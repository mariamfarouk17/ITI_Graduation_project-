#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

#include "../../LIB/STD_TYPES.h"

/* ADC Channels */
#define ADC_CHANNEL_0    0
#define ADC_CHANNEL_1    1
#define ADC_CHANNEL_2    2
#define ADC_CHANNEL_3    3
#define ADC_CHANNEL_4    4
#define ADC_CHANNEL_5    5
#define ADC_CHANNEL_6    6
#define ADC_CHANNEL_7    7

/* ADC Functions */
void MADC_vInit(void);

u16 MADC_u16AnalogRead(u8 A_u8Channel);

#endif /* MCAL_ADC_ADC_INT_H_ */