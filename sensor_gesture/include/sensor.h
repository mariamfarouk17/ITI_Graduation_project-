/*
 * sensor.h
 * Task 1: Sensor Acquisition & Gesture Recognition
 * Gesture-to-Speech Project (ATmega32)
 *
 * Declares the sensor data structure and the sensor acquisition
 * interface (init/read). This module is intentionally kept
 * independent from gesture recognition (gesture.h/gesture.c).
 *
 * Current implementation (in sensor.c) will use MOCK data since
 * real hardware is not yet connected. The function signatures
 * below are designed so that the mock implementation can later
 * be replaced with real ATmega32 ADC reading code WITHOUT any
 * changes required in gesture.c.
 *
 * This file does NOT contain ADC, LCD, UART, DFPlayer, or
 * audio-related code.
 */

#ifndef SENSOR_H
#define SENSOR_H

#include "config.h"

/* ---------------------------------------------------------
 * SensorData
 *
 * Holds one raw reading per flex sensor (per finger).
 * The meaning/scale of each value (mock range vs real ADC
 * range) depends on the current sensor.c implementation.
 * --------------------------------------------------------- */
typedef struct {
    int thumb_value;
    int index_value;
    int middle_value;
    int ring_value;
    int pinky_value;
} SensorData;

/* ---------------------------------------------------------
 * sensor_init
 *
 * Prepares the sensor subsystem for reading.
 * - In the current mock stage: may initialize mock data
 *   generation (e.g. seed a pseudo-random generator).
 * - In the future hardware stage: will configure the ATmega32
 *   ADC peripheral instead.
 *
 * Gesture recognition code should never need to know which
 * of the above this function actually does.
 * --------------------------------------------------------- */
void sensor_init(void);

/* ---------------------------------------------------------
 * sensor_read
 *
 * Acquires one reading from each of the five flex sensors and
 * returns them as a SensorData struct.
 * - In the current mock stage: values are temporary/test data.
 * - In the future hardware stage: values will come from real
 *   ADC conversions.
 *
 * The return type and behavior contract stay the same across
 * both stages, so gesture.c can consume this function without
 * modification.
 * --------------------------------------------------------- */
SensorData sensor_read(void);

#endif /* SENSOR_H */