#ifndef IR_INT_H
#define IR_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"

void IR_Init(u8 port, u8 pin);
u8   IR_IsBlackLine(u8 port, u8 pin);

#endif