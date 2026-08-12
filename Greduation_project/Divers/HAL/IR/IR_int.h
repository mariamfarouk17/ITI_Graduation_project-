#ifndef IR_INT_H_
#define IR_INT_H_

#define IR_PORT    DIO_PORTA
#define IR_PIN     DIO_PIN0

void IR_Init(void);
u8 IR_IsBlackLine(void);

#endif
