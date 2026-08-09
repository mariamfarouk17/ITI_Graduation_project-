#include <stdio.h>

#include "../sensor_gesture/include/sensor.h"
#include "../sensor_gesture/include/gesture.h"

int main(void)
{
    SensorData sensor_data;
    Gesture gesture;

    /* Initialize sensor module */
    sensor_init();

    /* Read sensor values */
    sensor_data = sensor_read();

    /* Recognize gesture */
    gesture = gesture_recognize(sensor_data);

    /* Print sensor values */
    printf("Sensor Values:\n");

    printf("Thumb  : %d\n", sensor_data.thumb_value);
    printf("Index  : %d\n", sensor_data.index_value);
    printf("Middle : %d\n", sensor_data.middle_value);
    printf("Ring   : %d\n", sensor_data.ring_value);
    printf("Pinky  : %d\n", sensor_data.pinky_value);

    /* Print recognized gesture */
    printf("\nRecognized Gesture: %s\n",
           gesture_to_string(gesture));

    return 0;
}