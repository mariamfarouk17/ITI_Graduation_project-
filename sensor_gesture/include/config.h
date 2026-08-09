/*
 * config.h
 * Task 1: Sensor Acquisition & Gesture Recognition
 * Gesture-to-Speech Project (ATmega32)
 *
 * This file contains general configuration constants for the
 * sensor and gesture modules.
 *
 * IMPORTANT:
 * All MOCK_* values and thresholds in this file are TEMPORARY
 * placeholder values used ONLY for software development and
 * testing before real flex sensor hardware is connected.
 * They are NOT calibrated hardware values.
 * They MUST be reviewed and replaced once real sensors are
 * wired up and calibrated.
 *
 * This file does NOT contain ADC, LCD, UART, DFPlayer, or
 * audio-related code/constants. Those belong in their own
 * modules/headers.
 */

#ifndef CONFIG_H
#define CONFIG_H

/* ---------------------------------------------------------
 * General sensor configuration
 * --------------------------------------------------------- */

/* Total number of flex sensors used by the system */
#define NUM_SENSORS 5

/* ---------------------------------------------------------
 * Finger index labels
 * Used so code can reference sensor arrays by name instead
 * of raw numeric indices (e.g. sensor_values[FINGER_INDEX]).
 * --------------------------------------------------------- */

#define FINGER_THUMB   0
#define FINGER_INDEX   1
#define FINGER_MIDDLE  2
#define FINGER_RING    3
#define FINGER_PINKY   4

/* ---------------------------------------------------------
 * MOCK / TEMPORARY sensor value range
 *
 * These bounds mimic a 10-bit ADC range (0-1023), only so
 * mock data generation/testing has a realistic scale to work
 * with. They do NOT represent actual calibrated hardware
 * limits.
 * --------------------------------------------------------- */

#define MOCK_SENSOR_MIN 0
#define MOCK_SENSOR_MAX 1023

/* ---------------------------------------------------------
 * MOCK / TEMPORARY gesture threshold
 *
 * Used by gesture.c during development to decide whether a
 * (mock) sensor reading should be treated as "finger bent" or
 * "finger straight". This is a placeholder only and WILL be
 * replaced after real hardware calibration.
 * --------------------------------------------------------- */

#define MOCK_FLEX_THRESHOLD 512

/* ---------------------------------------------------------
 * MOCK / TEMPORARY fixed test values per finger
 *
 * These provide predictable, repeatable input values for unit
 * tests (tests/test_sensor.c, tests/test_gesture.c) instead of
 * relying on random or live sensor data. Replace or remove
 * once real sensors are integrated.
 * --------------------------------------------------------- */

#define MOCK_THUMB_TEST_VALUE   100
#define MOCK_INDEX_TEST_VALUE   100
#define MOCK_MIDDLE_TEST_VALUE  100
#define MOCK_RING_TEST_VALUE    100
#define MOCK_PINKY_TEST_VALUE   100

/* ---------------------------------------------------------
 * MOCK / TEMPORARY timing constant
 *
 * Placeholder debounce time (in milliseconds) for stabilizing
 * gesture detection before a reading is accepted. May be
 * tuned/replaced after real-world testing.
 * --------------------------------------------------------- */

#define GESTURE_DEBOUNCE_MS 50

#define SENSOR_USE_MOCK 1

#endif /* CONFIG_H */