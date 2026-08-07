/*
 * test_gesture.c
 * Task 1: Sensor Acquisition & Gesture Recognition
 * Gesture-to-Speech Project (ATmega32)
 *
 * Unit tests for src/gesture.c (threshold-based mock-stage
 * recognition).
 *
 * Framework: plain C assert.h (same approach as test_sensor.c).
 * These tests run on a host machine, use explicit fixed
 * SensorData inputs (fully deterministic), and require no
 * physical hardware.
 *
 * Scope:
 * - Tests gesture_recognize() and gesture_to_string() only.
 * - Does NOT test sensor acquisition (see test_sensor.c).
 * - Does NOT test LCD, UART, DFPlayer, or audio functionality.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../include/gesture.h"
#include "../include/sensor.h"

/* ---------------------------------------------------------
 * Test 1: HELLO gesture
 * All fingers straight (values below threshold).
 * --------------------------------------------------------- */
static void test_gesture_hello(void)
{
    SensorData data = {100, 100, 100, 100, 100};

    Gesture result = gesture_recognize(data);
    assert(result == GESTURE_HELLO);
    assert(strcmp(gesture_to_string(result), "HELLO") == 0);

    printf("test_gesture_hello: PASSED\n");
}

/* ---------------------------------------------------------
 * Test 2: HELP gesture
 * All fingers bent (values above threshold).
 * --------------------------------------------------------- */
static void test_gesture_help(void)
{
    SensorData data = {700, 700, 700, 700, 700};

    Gesture result = gesture_recognize(data);
    assert(result == GESTURE_HELP);
    assert(strcmp(gesture_to_string(result), "HELP") == 0);

    printf("test_gesture_help: PASSED\n");
}

/* ---------------------------------------------------------
 * Test 3: YES gesture
 * Only index finger straight, rest bent.
 * --------------------------------------------------------- */
static void test_gesture_yes(void)
{
    SensorData data = {700, 100, 700, 700, 700};

    Gesture result = gesture_recognize(data);
    assert(result == GESTURE_YES);
    assert(strcmp(gesture_to_string(result), "YES") == 0);

    printf("test_gesture_yes: PASSED\n");
}

/* ---------------------------------------------------------
 * Test 4: NO gesture
 * Index and middle fingers straight, rest bent.
 * --------------------------------------------------------- */
static void test_gesture_no(void)
{
    SensorData data = {700, 100, 100, 700, 700};

    Gesture result = gesture_recognize(data);
    assert(result == GESTURE_NO);
    assert(strcmp(gesture_to_string(result), "NO") == 0);

    printf("test_gesture_no: PASSED\n");
}

/* ---------------------------------------------------------
 * Test 5: UNKNOWN gesture
 * A pattern that does not match any defined gesture:
 * thumb straight, index bent, middle bent, ring straight,
 * pinky bent.
 * --------------------------------------------------------- */
static void test_gesture_unknown(void)
{
    SensorData data = {100, 700, 700, 100, 700};

    Gesture result = gesture_recognize(data);
    assert(result == GESTURE_UNKNOWN);
    assert(strcmp(gesture_to_string(result), "UNKNOWN") == 0);

    printf("test_gesture_unknown: PASSED\n");
}

/* ---------------------------------------------------------
 * Test runner
 * --------------------------------------------------------- */
int main(void)
{
    test_gesture_hello();
    test_gesture_help();
    test_gesture_yes();
    test_gesture_no();
    test_gesture_unknown();

    printf("All gesture tests PASSED.\n");
    return 0;
}