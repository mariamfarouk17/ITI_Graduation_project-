#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

#include <avr/io.h>

#define IR_PIN PA0

void IR_Init(void);
u8 IR_IsBlackLine(void);

#endif
