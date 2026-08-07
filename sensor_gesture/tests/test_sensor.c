/*
 * test_sensor.c
 * Task 1: Sensor Acquisition & Gesture Recognition
 * Gesture-to-Speech Project (ATmega32)
 *
 * Unit tests for src/sensor.c (MOCK implementation).
 *
 * Framework:
 * Plain C assert.h - no external testing framework required.
 *
 * These tests are executed on the host computer, not on the ATmega32.
 * They validate the sensor module before real hardware integration.
 *
 * Scope:
 * - Tests sensor_init()
 * - Tests sensor_read()
 * - Verifies that the mock sensor values are exactly the values
 *   defined in config.h.
 *
 * Does NOT test:
 * - Gesture recognition
 * - ADC hardware
 * - LCD
 * - UART
 * - DFPlayer
 * - Audio
 */

#include <assert.h>
#include <stdio.h>

#include "../include/sensor.h"
#include "../include/config.h"

/* ---------------------------------------------------------
 * Test 1: sensor_init()
 *
 * The function should execute successfully without crashing.
 * --------------------------------------------------------- */
static void test_sensor_init_runs_ok(void)
{
    sensor_init();

    printf("test_sensor_init_runs_ok: PASSED\n");
}

/* ---------------------------------------------------------
 * Test 2: Sensor values are within the valid mock range.
 *
 * This checks that every returned value is between:
 * MOCK_SENSOR_MIN and MOCK_SENSOR_MAX.
 * --------------------------------------------------------- */
static void test_sensor_read_values_in_range(void)
{
    SensorData data = sensor_read();

    assert(data.thumb_value >= MOCK_SENSOR_MIN &&
           data.thumb_value <= MOCK_SENSOR_MAX);

    assert(data.index_value >= MOCK_SENSOR_MIN &&
           data.index_value <= MOCK_SENSOR_MAX);

    assert(data.middle_value >= MOCK_SENSOR_MIN &&
           data.middle_value <= MOCK_SENSOR_MAX);

    assert(data.ring_value >= MOCK_SENSOR_MIN &&
           data.ring_value <= MOCK_SENSOR_MAX);

    assert(data.pinky_value >= MOCK_SENSOR_MIN &&
           data.pinky_value <= MOCK_SENSOR_MAX);

    printf("test_sensor_read_values_in_range: PASSED\n");
}

/* ---------------------------------------------------------
 * Test 3: Verify the EXACT mock values.
 *
 * These values come from config.h:
 *
 * Thumb  = 300
 * Index  = 700
 * Middle = 650
 * Ring   = 400
 * Pinky  = 200
 *
 * This test ensures sensor_read() is actually using the
 * predefined mock values rather than random values.
 * --------------------------------------------------------- */
static void test_sensor_read_returns_expected_mock_values(void)
{
    SensorData data = sensor_read();

    assert(data.thumb_value == MOCK_THUMB_TEST_VALUE);
    assert(data.index_value == MOCK_INDEX_TEST_VALUE);
    assert(data.middle_value == MOCK_MIDDLE_TEST_VALUE);
    assert(data.ring_value == MOCK_RING_TEST_VALUE);
    assert(data.pinky_value == MOCK_PINKY_TEST_VALUE);

    printf("test_sensor_read_returns_expected_mock_values: PASSED\n");
}

/* ---------------------------------------------------------
 * Test 4: Verify that repeated sensor_read() calls return
 * the same mock values.
 *
 * Since the current implementation uses fixed mock data,
 * repeated calls should produce identical results.
 *
 * This behavior is intentional for deterministic testing.
 * --------------------------------------------------------- */
static void test_sensor_read_is_deterministic(void)
{
    SensorData first = sensor_read();
    SensorData second = sensor_read();

    assert(first.thumb_value == second.thumb_value);
    assert(first.index_value == second.index_value);
    assert(first.middle_value == second.middle_value);
    assert(first.ring_value == second.ring_value);
    assert(first.pinky_value == second.pinky_value);

    printf("test_sensor_read_is_deterministic: PASSED\n");
}

/* ---------------------------------------------------------
 * Test runner
 * --------------------------------------------------------- */
int main(void)
{
    printf("========================================\n");
    printf("Running Sensor Module Tests\n");
    printf("========================================\n\n");

    test_sensor_init_runs_ok();
    test_sensor_read_values_in_range();
    test_sensor_read_returns_expected_mock_values();
    test_sensor_read_is_deterministic();

    printf("\n========================================\n");
    printf("All sensor tests PASSED.\n");
    printf("========================================\n");

    return 0;
}