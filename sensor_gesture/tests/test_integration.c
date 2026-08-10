/*
 * test_integration.c
 * Task 1: Sensor Acquisition & Gesture Recognition
 * Gesture-to-Speech Project (ATmega32)
 *
 * HOST-SIDE SOFTWARE INTEGRATION TEST
 * ------------------------------------
 * This file tests the full pipeline:
 *   sensor_init() -> sensor_read() -> gesture_recognize() -> gesture_to_string()
 *
 * IMPORTANT:
 * This is a host-side software integration test only.
 * It does NOT use real ATmega32 hardware and does NOT perform
 * any ADC access. It runs against the current MOCK sensor
 * implementation (fixed mock values defined in config.h).
 *
 * This file does NOT modify sensor.c, gesture.c, sensor.h,
 * gesture.h, or config.h, and does NOT test LCD, UART,
 * DFPlayer, or audio functionality.
 *
 * Framework: plain C assert.h (same approach as test_sensor.c
 * and test_gesture.c). No external testing framework is used.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../include/sensor.h"
#include "../include/gesture.h"
#include "../include/config.h"

/* ---------------------------------------------------------
 * test_full_pipeline_with_current_mock_values
 *
 * Exercises the complete pipeline using the CURRENT fixed
 * mock sensor values returned by sensor_read():
 *   thumb = 300, index = 700, middle = 650, ring = 400, pinky = 200
 *
 * Given MOCK_FLEX_THRESHOLD = 512 (bent if value > threshold):
 *   thumb  (300) -> straight
 *   index  (700) -> bent
 *   middle (650) -> bent
 *   ring   (400) -> straight
 *   pinky  (200) -> straight
 *
 * This pattern (straight, bent, bent, straight, straight)
 * does not match HELLO, HELP, YES, or NO, so the expected
 * result is GESTURE_UNKNOWN.
 * --------------------------------------------------------- */
static void test_full_pipeline_with_current_mock_values(void)
{
    /* Step 1: initialize the (mock) sensor subsystem */
    sensor_init();

    /* Step 2: acquire sensor data (mock values from sensor.c) */
    SensorData data = sensor_read();

    /* Step 3: run gesture recognition on the acquired data */
    Gesture result = gesture_recognize(data);

    /* Step 4: convert the recognized gesture to a readable string */
    const char *result_str = gesture_to_string(result);

    /* Verify the pipeline produced the expected result for the
     * current fixed mock values. */
    assert(result == GESTURE_UNKNOWN);
    assert(strcmp(result_str, "UNKNOWN") == 0);

    printf("test_full_pipeline_with_current_mock_values: PASSED "
           "(sensor_init -> sensor_read -> gesture_recognize -> "
           "gesture_to_string = %s)\n", result_str);
}

/* ---------------------------------------------------------
 * test_pipeline_result_is_stable_across_calls
 *
 * Confirms that repeated calls through the full pipeline
 * produce a consistent, deterministic result, since the mock
 * sensor values used here are fixed (not randomized) and the
 * recognition logic is purely threshold-based.
 * --------------------------------------------------------- */
static void test_pipeline_result_is_stable_across_calls(void)
{
    sensor_init();
    SensorData first_data = sensor_read();
    Gesture first_result = gesture_recognize(first_data);

    sensor_init();
    SensorData second_data = sensor_read();
    Gesture second_result = gesture_recognize(second_data);

    assert(first_result == second_result);
    assert(strcmp(gesture_to_string(first_result),
                   gesture_to_string(second_result)) == 0);

    printf("test_pipeline_result_is_stable_across_calls: PASSED "
           "(result = %s)\n", gesture_to_string(first_result));
}

/* ---------------------------------------------------------
 * Integration test runner
 * --------------------------------------------------------- */
int main(void)
{
    test_full_pipeline_with_current_mock_values();
    test_pipeline_result_is_stable_across_calls();

    printf("All integration tests PASSED.\n");
    return 0;
}