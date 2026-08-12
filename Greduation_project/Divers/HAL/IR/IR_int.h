#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

#include "STD_TYPES.h"
#include "DIO_interface.h"

#define IR_PORT    DIO_PORTA
#define IR_PIN     DIO_PIN0

void IR_Init(void);
uint8_t IR_IsBlackLine(void);

#endif
