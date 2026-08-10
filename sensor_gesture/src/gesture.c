/*
 * gesture.c
 * Task 1: Sensor Acquisition & Gesture Recognition
 * Gesture-to-Speech Project (ATmega32)
 *
 * Implements gesture_recognize() and gesture_to_string()
 * declared in gesture.h.
 *
 * CURRENT STATUS: THRESHOLD-BASED MOCK-STAGE LOGIC
 * ---------------------------------------------------
 * Recognition uses simple bent/straight classification per
 * finger, based on MOCK_FLEX_THRESHOLD from config.h.
 *
 * IMPORTANT: These thresholds and finger patterns are
 * TEMPORARY. They are based on mock sensor data assumptions
 * (higher value = more bent finger) and have NOT been
 * calibrated against real flex sensor hardware. They MUST be
 * reviewed and retuned once real sensors are connected and
 * calibrated.
 *
 * This file contains NO LCD, UART, DFPlayer, audio, or
 * main-loop code, and is independent of how SensorData was
 * acquired (mock or real ADC).
 */

#include "gesture.h"
#include "config.h"

/* ---------------------------------------------------------
 * is_bent
 *
 * Classifies a single sensor value as "bent" (1) or
 * "straight" (0) based on MOCK_FLEX_THRESHOLD.
 *
 * ASSUMPTION (temporary, unverified on real hardware):
 * higher sensor value = more bent finger.
 * --------------------------------------------------------- */
static int is_bent(int value)
{
    return (value > MOCK_FLEX_THRESHOLD) ? 1 : 0;
}

/* ---------------------------------------------------------
 * gesture_recognize
 *
 * Classifies each finger as bent/straight, then matches the
 * resulting pattern against known temporary gesture
 * definitions. Returns GESTURE_UNKNOWN if no exact match.
 * --------------------------------------------------------- */
Gesture gesture_recognize(SensorData data)
{
    int thumb  = is_bent(data.thumb_value);
    int index  = is_bent(data.index_value);
    int middle = is_bent(data.middle_value);
    int ring   = is_bent(data.ring_value);
    int pinky  = is_bent(data.pinky_value);

    /* HELLO: all fingers straight (open hand) */
    if (!thumb && !index && !middle && !ring && !pinky) {
        return GESTURE_HELLO;
    }

    /* HELP: all fingers bent (closed fist) */
    if (thumb && index && middle && ring && pinky) {
        return GESTURE_HELP;
    }

    /* YES: only index finger straight, rest bent */
    if (thumb && !index && middle && ring && pinky) {
        return GESTURE_YES;
    }

    /* NO: index and middle straight, rest bent */
    if (thumb && !index && !middle && ring && pinky) {
        return GESTURE_NO;
    }

    /* No known pattern matched */
    return GESTURE_UNKNOWN;
}

/* ---------------------------------------------------------
 * gesture_to_string
 *
 * Returns a readable string for a given Gesture value, for
 * debugging/logging purposes only (no output hardware logic).
 * --------------------------------------------------------- */
const char *gesture_to_string(Gesture gesture)
{
    switch (gesture) {
        case GESTURE_HELLO:
            return "HELLO";
        case GESTURE_HELP:
            return "HELP";
        case GESTURE_YES:
            return "YES";
        case GESTURE_NO:
            return "NO";
        case GESTURE_UNKNOWN:
        default:
            return "UNKNOWN";
    }
}