/*
 * FLEX_SENSOR_prg.c
 *
 * Flex Sensor Abstraction Layer - Implementation File
 * Hand Gesture to Speech System (ATmega32)
 *
 * Implements MFLEX_SENSOR_vInit(), MFLEX_SENSOR_xReadAll(),
 * and MFLEX_SENSOR_u16Read() declared in FLEX_SENSOR_int.h.
 *
 * This module uses ONLY the existing ADC driver API
 * (MADC_vInit, MADC_u16AnalogRead). It does NOT access any
 * ADC registers directly, does NOT implement a new ADC or
 * DIO driver, and does NOT modify existing drivers.
 *
 * All returned sensor values are raw, uncalibrated 10-bit
 * ADC readings (0-1023). Gesture interpretation/thresholds
 * are handled by a separate module, not here.
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/ADC/ADC_int.h"
#include "FLEX_SENSOR_int.h"

/* ---------------------------------------------------------
 * MFLEX_SENSOR_vInit
 *
 * Initializes the ADC driver used by this module. The
 * application should call this once before reading any flex
 * sensor data.
 * --------------------------------------------------------- */
void MFLEX_SENSOR_vInit(void)
{
    MADC_vInit();
}

/* ---------------------------------------------------------
 * MFLEX_SENSOR_u16Read
 *
 * Maps a sensor index (finger) to its corresponding ADC
 * channel and reads it via MADC_u16AnalogRead().
 *
 * Channel mapping:
 *   FLEX_SENSOR_THUMB  -> CHANNEL_0
 *   FLEX_SENSOR_INDEX  -> CHANNEL_1
 *   FLEX_SENSOR_MIDDLE -> CHANNEL_2
 *   FLEX_SENSOR_RING   -> CHANNEL_3
 *   FLEX_SENSOR_PINKY  -> CHANNEL_4
 *
 * Returns the raw, uncalibrated 10-bit ADC reading (0-1023).
 * Returns 0 for an invalid/unknown sensor index.
 * --------------------------------------------------------- */
u16 MFLEX_SENSOR_u16Read(u8 A_u8SensorIndex)
{
    u16 L_u16Value = 0;

    switch (A_u8SensorIndex)
    {
        case FLEX_SENSOR_THUMB:
            L_u16Value = MADC_u16AnalogRead(ADC_CHANNEL_0);
            break;

        case FLEX_SENSOR_INDEX:
            L_u16Value = MADC_u16AnalogRead(ADC_CHANNEL_1);
            break;

        case FLEX_SENSOR_MIDDLE:
            L_u16Value = MADC_u16AnalogRead(ADC_CHANNEL_2);
            break;

        case FLEX_SENSOR_RING:
            L_u16Value = MADC_u16AnalogRead(ADC_CHANNEL_3);
            break;

        case FLEX_SENSOR_PINKY:
            L_u16Value = MADC_u16AnalogRead(ADC_CHANNEL_4);
            break;

        default:
            L_u16Value = 0;
            break;
    }

    return L_u16Value;
}

/* ---------------------------------------------------------
 * MFLEX_SENSOR_xReadAll
 *
 * Reads all five flex sensors in sequence (thumb, index,
 * middle, ring, pinky) using MFLEX_SENSOR_u16Read() and
 * returns them packed into a FlexSensorData structure.
 * --------------------------------------------------------- */
FlexSensorData MFLEX_SENSOR_xReadAll(void)
{
    FlexSensorData L_xData;

    L_xData.thumb  = MFLEX_SENSOR_u16Read(FLEX_SENSOR_THUMB);
    L_xData.index  = MFLEX_SENSOR_u16Read(FLEX_SENSOR_INDEX);
    L_xData.middle = MFLEX_SENSOR_u16Read(FLEX_SENSOR_MIDDLE);
    L_xData.ring   = MFLEX_SENSOR_u16Read(FLEX_SENSOR_RING);
    L_xData.pinky  = MFLEX_SENSOR_u16Read(FLEX_SENSOR_PINKY);

    return L_xData;
}