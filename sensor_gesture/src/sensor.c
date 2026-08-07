/*
 * sensor.c
 * Task 1: Sensor Acquisition & Gesture Recognition
 * Gesture-to-Speech Project (ATmega32)
 *
 * Implements sensor_init() and sensor_read() declared in sensor.h.
 *
 * CURRENT STATUS: MOCK IMPLEMENTATION
 *
 * The physical flex sensors are NOT connected yet.
 * Therefore, sensor_read() returns fixed mock values defined
 * in config.h.
 *
 * These values are used only for software development and testing.
 * They are NOT real sensor readings and are NOT calibrated hardware values.
 *
 * When the real hardware is connected, this module will be updated
 * to read the ATmega32 ADC channels instead.
 *
 * This file does NOT contain:
 * - Gesture recognition
 * - LCD
 * - UART
 * - DFPlayer
 * - Audio
 */

#include "sensor.h"
#include "config.h"

/*
 * sensor_init
 *
 * Initializes the sensor subsystem.
 *
 * In the current mock implementation, there is nothing to initialize.
 *
 * In the future, this function will configure the ATmega32 ADC.
 */
void sensor_init(void)
{
    /*
     * Nothing to initialize for the mock sensor.
     *
     * Real hardware ADC initialization will be added later.
     */
}

/*
 * sensor_read
 *
 * Returns one reading for each of the five flex sensors.
 *
 * CURRENT MOCK IMPLEMENTATION:
 * The function returns fixed test values from config.h.
 *
 * These values allow us to test the gesture recognition logic
 * before connecting the real sensors.
 */
SensorData sensor_read(void)
{
    SensorData data;

    /*
     * Temporary mock values.
     *
     * These are NOT real hardware measurements.
     * They will be replaced by ADC readings after
     * the flex sensors are connected and calibrated.
     */
    data.thumb_value  = MOCK_THUMB_TEST_VALUE;
    data.index_value  = MOCK_INDEX_TEST_VALUE;
    data.middle_value = MOCK_MIDDLE_TEST_VALUE;
    data.ring_value   = MOCK_RING_TEST_VALUE;
    data.pinky_value  = MOCK_PINKY_TEST_VALUE;

    return data;
}