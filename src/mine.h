#ifndef MINE_H_
#define MINE_H_
#include <pebble.h>
#include "game.h"

typedef struct Mine_S {
    BitmapLayer* layer;
    Vector2 pos, vel;
    double center_y, time_off;
} Mine;

Mine* create_mine(GBitmap* image);
void destroy_mine(Mine* mine);
void update_mine(Mine* mine);
#endif