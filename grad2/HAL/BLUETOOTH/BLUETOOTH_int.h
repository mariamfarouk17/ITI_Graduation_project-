/*
 * BLUETOOTH_int.h
 *
 *  Created on: Aug 11, 2026
 *      Author: HP
 */

#ifndef HAL_BLUETOOTH_BLUETOOTH_INT_H_
#define HAL_BLUETOOTH_BLUETOOTH_INT_H_

void HBLUETOOTH_vINIT(void);

void HBLUETOOTH_vSendChar(u8 A_u8Data);

void HBLUETOOTH_vSendString(const u8 A_u8String[]);

u8 HBLUETOOTH_u8ReceiveChar(void);

u8 HBLUETOOTH_u8DataAvailable(void);

#endif /* HAL_BLUETOOTH_BLUETOOTH_INT_H_ */
