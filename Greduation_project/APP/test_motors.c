///*
// * motor_test.c
// * Simple L298 motor test — verify wiring & direction before full integration
// */
//
//#include <avr/io.h>
//#include <util/delay.h>
//#include "../Divers/MCAL/DIO/DIO_int.h"
//#include "../Divers/LIB/STD_TYPES.h"
//#include "../Divers/HAL/L298/L298_int.h"
//
//#define TEST_SPEED   100u
//#define STEP_DELAY   1500   // ms to run each movement
//#define PAUSE_DELAY  500    // ms stop between movements
//
//static void motor_vTestStep(u8 direction, u8 speed, u16 run_ms, const char *label);
//
//int main(void)
//{
//    L298_vInit();
//    L298_vMove(MOVE_STOP, 0u);
//    _delay_ms(1000); // settle time before test starts
//
//    while (1)
//    {
//        motor_vTestStep(MOVE_FORWARD,  TEST_SPEED, STEP_DELAY, "FORWARD");
//        motor_vTestStep(MOVE_BACKWARD, TEST_SPEED, STEP_DELAY, "BACKWARD");
//        motor_vTestStep(MOVE_LEFT,     TEST_SPEED, STEP_DELAY, "LEFT");
//        motor_vTestStep(MOVE_RIGHT,    TEST_SPEED, STEP_DELAY, "RIGHT");
//
//        // full stop + long pause before repeating the cycle
//        L298_vMove(MOVE_STOP, 0u);
//        _delay_ms(2000);
//    }
//}
//
//static void motor_vTestStep(u8 direction, u8 speed, u16 run_ms, const char *label)
//{
//    (void)label; // no UART here; keep param for readability / future debug print
//
//    L298_vMove(direction, speed);
//
//    // busy-wait in fixed chunks since _delay_ms needs a compile-time constant
//    for (u16 elapsed = 0; elapsed < run_ms; elapsed += 100)
//    {
//        _delay_ms(100);
//    }
//
//    L298_vMove(MOVE_STOP, 0u);
//    _delay_ms(PAUSE_DELAY);
//}
