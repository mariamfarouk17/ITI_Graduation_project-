/*
 * ADC_int.h
 *
 *  Created on: Aug 2, 2026
 *      Author: HP
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

#define Channel_0    0
#define Channel_1    1
#define Channel_2    2
#define Channel_3    3
#define Channel_4    4
#define Channel_5    5
#define Channel_6    6
#define Channel_7    7

void MADC_vINIT(void);

//Read Value from Sensor
u16 MADC_u16ReadAnalogValue(u8 A_u8ChannelNum);

#endif /* MCAL_ADC_ADC_INT_H_ */
