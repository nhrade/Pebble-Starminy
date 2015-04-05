#include <pebble.h>
#include "accelerometer_manager.h"

void get_accel_data(AccelData* data) {
    accel_service_peek(data); 
}
