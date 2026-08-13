# Bluetooth Driver Quick Reference

## API Overview

### Initialization
```c
void BLUETOOTH_Init(void);
```
- Initializes USART module for Bluetooth communication
- Must be called once at startup before using Tx/Rx functions
- Configures baud rate and other USART settings from USART driver config

### Transmission
```c
void BLUETOOTH_Transmit(u8 A_u8Byte);
```
- Sends a single byte via Bluetooth
- Waits for USART transmitter to be ready
- Blocking function
- **Example:**
  ```c
  BLUETOOTH_Transmit('H');  // Send 'H' character
  BLUETOOTH_Transmit(0x42); // Send 0x42 byte
  ```

### Reception
```c
u8 BLUETOOTH_Receive(void);
```
- Receives a single byte from Bluetooth
- **Blocking function** - waits until data arrives
- Returns the received byte
- **Note:** Typically used in ISR context, not in main loop
- **Example:**
  ```c
  u8 data = BLUETOOTH_Receive();  // Wait for data
  ```

---

## Supported Motor Commands

| Command | Action | Speed |
|---------|--------|-------|
| **F** | Move Forward | MANUAL_SPEED (60) |
| **B** | Move Backward | MANUAL_SPEED (60) |
| **R** | Turn Right | MANUAL_SPEED (60) |
| **L** | Turn Left | MANUAL_SPEED (60) |
| **S** | Stop | 0 |
| Other | Ignored | - |

---

## Setup Instructions

### 1. Basic Manual Control
```c
#include "../Divers/HAL/BLUETOOTH/BLUETOOTH_int.h"
#include "../Divers/HAL/L298/L298_int.h"
#include <avr/interrupt.h>

ISR(USART_RXC_vect)
{
    u8 cmd = BLUETOOTH_Receive();
    // Process command...
}

int main(void)
{
    BLUETOOTH_Init();
    L298_vInit();
    sei();  // Enable interrupts
    
    while(1);  // Wait for ISR
}
```

### 2. With Transmission Testing
```c
// Send startup message
BLUETOOTH_Transmit('S');
BLUETOOTH_Transmit('T');
BLUETOOTH_Transmit('A');
BLUETOOTH_Transmit('R');
BLUETOOTH_Transmit('T');
```

### 3. Error Handling
```c
ISR(USART_RXC_vect)
{
    u8 cmd = BLUETOOTH_Receive();
    
    if (cmd >= 'A' && cmd <= 'Z')
    {
        // Valid range - process
    }
    else
    {
        // Invalid - ignore silently or log
    }
}
```

---

## Common Issues & Solutions

### Issue: Commands Not Responding
- [ ] Check if `sei()` (enable interrupts) is called
- [ ] Verify USART initialization succeeded
- [ ] Check USART baud rate configuration matches Bluetooth module
- [ ] Verify USART_RXC interrupt vector is used correctly

### Issue: Garbled Data
- [ ] Verify baud rate (typically 9600 or 115200)
- [ ] Check Bluetooth module configuration
- [ ] Ensure proper wiring to AVR USART pins

### Issue: Transmission Not Working
- [ ] Verify Bluetooth module is powered
- [ ] Check USART TX pin connectivity
- [ ] Confirm BLUETOOTH_Transmit() is being called
- [ ] Use advanced test to verify transmission capability

### Issue: Motor Not Stopping
- [ ] Verify L298_vInit() was called
- [ ] Check if 'S' command is being sent correctly
- [ ] Verify motor driver wiring

---

## Testing Checklist

- [ ] BLUETOOTH_Init() called at startup
- [ ] Interrupts enabled with sei()
- [ ] Commands sent from mobile app/terminal
- [ ] Motor responds to F/B/R/L/S commands
- [ ] Motor stops on 'S' command
- [ ] Invalid commands ignored safely
- [ ] No crashes or resets on unexpected input

---

## Use Cases

### Scenario 1: Simple Manual Control
**File:** `test_bluetooth.c` (standard test)
**Use When:** Real-time manual control via Bluetooth is needed

### Scenario 2: Testing & Debugging
**File:** `test_bluetooth_advanced.c` (advanced test)
**Use When:** 
- Debugging communication issues
- Testing transmission capability
- Validating command processing
- Monitoring command statistics

### Scenario 3: Production Autonomous Mode + Manual Override
**Implementation:** Use ISR to switch between modes
```c
volatile u8 g_mode = 1;  // 1=Auto, 0=Manual

ISR(USART_RXC_vect)
{
    u8 cmd = BLUETOOTH_Receive();
    
    if (cmd == 'A')
        g_mode = 1;  // Switch to autonomous
    else if (cmd == 'M')
        g_mode = 0;  // Switch to manual
    else if (g_mode == 0)
        ProcessCommand(cmd);  // Manual control only
}
```

---

## Function Timing

| Operation | Type | Notes |
|-----------|------|-------|
| BLUETOOTH_Init() | Initialization | Called once at startup |
| BLUETOOTH_Transmit() | Blocking | Waits ~100-1000 µs per byte |
| BLUETOOTH_Receive() | Blocking | Waits until data available |

**Note:** RECEIVE is typically used in ISR where byte is guaranteed available

---

## Hardware Requirements

- **Microcontroller:** AVR (ATmega32/ATmega128/similar)
- **Bluetooth Module:** HC-05 or HC-06 recommended
- **USART:** Standard AVR USART peripheral
- **Baud Rate:** 9600 bps (default, configure in USART driver)
- **Communication:** Asynchronous serial (8 data, 1 stop, no parity)

---

## Wiring Diagram

```
AVR USART          HC-05 Module
───────────        ────────────
  TX (PD1) ◄──────► RX (Blue)
  RX (PD0) ◄──────► TX (Green)
  GND      ◄──────► GND (Black)
  +5V      ◄──────► 5V (Red, via level shifter if needed)
```

---

## Modification History

| Date | Change | Status |
|------|--------|--------|
| 2026-08-13 | Initial modifications | ✅ Complete |
| - | Documentation | ✅ Complete |
| - | Header guard fix | ✅ Complete |
| - | Advanced test creation | ✅ Complete |

---

**Last Updated:** 2026-08-13
**Version:** 1.0 Final
