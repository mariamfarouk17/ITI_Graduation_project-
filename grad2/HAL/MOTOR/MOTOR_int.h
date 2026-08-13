/*
 * MOTOR_int.h
 *
 *  Created on: Aug 11, 2026
 *      Author: HP
 */

#ifndef HAL_MOTOR_MOTOR_INT_H_
#define HAL_MOTOR_MOTOR_INT_H_

#define MOTOR_1    0
#define MOTOR_2    1

#define MOTOR_STOP       0
#define MOTOR_FORWARD    1
#define MOTOR_BACKWARD   2

void HMOTOR_vINIT(void);

void HMOTOR_vSetSpeed(u8 A_u8MotorID, u8 A_u8Speed);

void HMOTOR_vSetDirection(u8 A_u8MotorID, u8 A_u8Direction);

void HMOTOR_vStop(u8 A_u8MotorID);

#endif /* HAL_MOTOR_MOTOR_INT_H_ */
