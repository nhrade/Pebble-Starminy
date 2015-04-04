#include <pebble.h>
#ifndef ACCELERATION_H_
#define ACCELERATION_H_

//-----Constant Definitions------
#define FORWARD 0
#define BACKWARDS 1
#define LEFT 2
#define RIGHT 3
#define UP 4
#define DOWN 5

    
//-------------------------------
    

typedef struct direction_s {
    uint32_t direction;
    uint32_t magnitude;
    
} Direction;

Direction* create_direction(AccelAxisType axis, int32_t direction);
void destroy_direction(Direction* direction);
char* direction_to_string(Direction* direction);

#endif