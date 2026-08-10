/*
 * FLEX_SENSOR_int.h
 *
 * Flex Sensor Abstraction Layer - Interface File
 * Hand Gesture to Speech System (ATmega32)
 *
 * This module sits between the application layer and the
 * existing ADC driver (MADC_vInit / MADC_u16AnalogRead).
 * It provides a simple, named API for reading the 5 flex
 * sensors (one per finger) without the application needing
 * to know about ADC channels directly.
 *
 * IMPORTANT:
 * All values returned by this module are RAW 10-bit ADC
 * readings (0 - 1023). They are NOT calibrated.
 * Do NOT assume any particular raw value means "bent" or
 * "straight" - that mapping depends on the physical flex
 * sensor, resistor, wiring, and voltage-divider setup, and
 * will be determined later during hardware calibration.
 *
 * This module does NOT implement gesture recognition,
 * thresholds, or calibration. It only acquires raw sensor
 * data.
 */

#ifndef FLEX_SENSOR_INT_H
#define FLEX_SENSOR_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_int.h"

/* ---------------------------------------------------------
 * Sensor index constants
 *
 * Used with MFLEX_SENSOR_u16Read() to select which finger's
 * sensor to read.
 * --------------------------------------------------------- */
#define FLEX_SENSOR_THUMB   0
#define FLEX_SENSOR_INDEX   1
#define FLEX_SENSOR_MIDDLE  2
#define FLEX_SENSOR_RING    3
#define FLEX_SENSOR_PINKY   4

#define FLEX_SENSOR_COUNT   5

/* ---------------------------------------------------------
 * FlexSensorData
 *
 * Holds one RAW ADC reading (0-1023, uncalibrated) per
 * finger flex sensor.
 * --------------------------------------------------------- */
typedef struct
{
    u16 thumb;
    u16 index;
    u16 middle;
    u16 ring;
    u16 pinky;
} FlexSensorData;

/* ---------------------------------------------------------
 * MFLEX_SENSOR_vInit
 *
 * Initializes the flex sensor module. Internally initializes
 * the ADC driver (MADC_vInit()) so the application does not
 * need to call the ADC driver directly.
 * --------------------------------------------------------- */
void MFLEX_SENSOR_vInit(void);

/* ---------------------------------------------------------
 * MFLEX_SENSOR_xReadAll
 *
 * Reads all five flex sensors (thumb, index, middle, ring,
 * pinky) and returns them as a FlexSensorData structure.
 * Values are raw, uncalibrated 10-bit ADC readings.
 * --------------------------------------------------------- */
FlexSensorData MFLEX_SENSOR_xReadAll(void);

/* ---------------------------------------------------------
 * MFLEX_SENSOR_u16Read
 *
 * Reads a single flex sensor selected by A_u8SensorIndex
 * (use FLEX_SENSOR_THUMB, FLEX_SENSOR_INDEX, etc.).
 * Returns the raw, uncalibrated 10-bit ADC reading (0-1023).
 * --------------------------------------------------------- */
u16 MFLEX_SENSOR_u16Read(u8 A_u8SensorIndex);

#endif /* FLEX_SENSOR_INT_H */