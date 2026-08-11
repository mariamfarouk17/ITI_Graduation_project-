/*
 * main.c
 * Author: shaima
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Divers/LIB/STD_TYPES.h"
#include "Divers/HAL/L298/L298_int.h"
#include "Divers/HAL/BLUETOOTH/BLUETOOTH_int.h"

volatile u8 g_mode = 1; // 1 = Auto, 0 = Manual

ISR(USART_RXC_vect)
{
    u8 read = BLUETOOTH_Receive();

    switch (read)
    {
        case 'A':
            g_mode = 1;
            break;
        case 'M':
            g_mode = 0;
            break;
        case 'F':
            if (g_mode == 0)
            {
                L298_vMove(MOVE_FORWARD, 100u);
            }
            break;
        case 'B':
            if (g_mode == 0)
            {
                L298_vMove(MOVE_BACKWARD, 100u);
            }
            break;
        case 'R':
            if (g_mode == 0)
            {
                L298_vMove(MOVE_RIGHT, 100u);
            }
            break;
        case 'L':
            if (g_mode == 0)
            {
                L298_vMove(MOVE_LEFT, 100u);
            }
            break;
        case 'S':
            if (g_mode == 0)
            {
                L298_vMove(MOVE_STOP, 0u);
            }
            break;
        default:
            break;
    }
}

int main(void)
{
    BLUETOOTH_Init();
    L298_vInit();
    sei();

    L298_vMove(MOVE_STOP, 0u);

    while (1)
    {
        if (g_mode == 1)
        {
            L298_vMove(MOVE_FORWARD, 100u);
            _delay_ms(100);
        }
    }
}

