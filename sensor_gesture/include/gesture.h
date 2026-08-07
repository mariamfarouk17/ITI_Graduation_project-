/*
 * gesture.h
 * Task 1: Sensor Acquisition & Gesture Recognition
 * Gesture-to-Speech Project (ATmega32)
 *
 * Declares the Gesture enum and the gesture recognition
 * interface. This module depends only on the SensorData
 * struct (from sensor.h) and is independent of how sensor
 * data is acquired (mock or real ADC hardware).
 *
 * This file does NOT contain ADC, LCD, UART, DFPlayer, or
 * audio-related code.
 */

#ifndef GESTURE_H
#define GESTURE_H

#include "sensor.h"

/* ---------------------------------------------------------
 * Gesture
 *
 * Represents a recognized hand gesture based on sensor data.
 * GESTURE_UNKNOWN is the default/fallback value used when no
 * defined gesture pattern is matched.
 * --------------------------------------------------------- */
typedef enum {
    GESTURE_UNKNOWN = 0,
    GESTURE_HELLO,
    GESTURE_HELP,
    GESTURE_YES,
    GESTURE_NO
} Gesture;

/* ---------------------------------------------------------
 * gesture_recognize
 *
 * Takes a SensorData struct (five finger readings) and
 * determines which Gesture it corresponds to.
 *
 * This function is independent of how the SensorData was
 * obtained (mock values today, real ADC readings later),
 * since it only operates on the struct contents.
 * --------------------------------------------------------- */
Gesture gesture_recognize(SensorData data);

/* ---------------------------------------------------------
 * gesture_to_string
 *
 * Converts a Gesture value into a readable string, useful for
 * debugging/logging during development. Contains no output
 * hardware logic (no UART/LCD/etc.).
 * --------------------------------------------------------- */
const char *gesture_to_string(Gesture gesture);

#endif /* GESTURE_H */