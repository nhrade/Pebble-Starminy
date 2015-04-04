#include <pebble.h>
#include <stdlib.h>
    
#include "acceleration.h"
#define GT_ZERO(dir) dir > 0   
    
Direction* create_direction(AccelAxisType axis, int32_t direction) {
    Direction* dir = malloc(sizeof(Direction));
    
    switch(axis) {
        case ACCEL_AXIS_X:
            if(GT_ZERO(direction))
                dir->direction = RIGHT;
            else
                dir->direction = LEFT;
            break;
        case ACCEL_AXIS_Y:
            if(GT_ZERO(direction))
                dir->direction = FORWARD;
            else
                dir->direction = BACKWARDS;
            break;
        case ACCEL_AXIS_Z:
            if(GT_ZERO(direction))
                dir->direction = UP;
            else
                dir->direction = DOWN;
            break;
    }
    dir->magnitude = abs(direction);
    return dir;
}

char* direction_to_string(Direction* dir) {
    switch(dir->direction) {
        case RIGHT:
            return "right"; break;
        case LEFT:
            return "left"; break;
        case FORWARD:
            return "forward"; break;
        case BACKWARDS:
            return "backwards"; break;
        case UP:
            return "up"; break;
        case DOWN:
            return "down"; break;
        default:
            return NULL; break;
    }
}

void destroy_direction(Direction* direction) {
    free(direction);
}