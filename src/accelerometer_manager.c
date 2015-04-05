#include <pebble.h>
#include "accelerometer_manager.h"

/*
* Gets accelerometer data, caller responsible for freeing allocated memory
*/
AccelData* get_accel_data() {
    AccelData* data = malloc(sizeof(AccelData));
    accel_service_peek(data);
    return data;
}
