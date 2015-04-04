#ifndef GAME_H_
#define GAME_H_
#include <pebble.h>


static Player* player;

typedef struct Vector2_S {
   double x, y;  
} Vector2;
    
typedef struct Player_S {
    Vector2 pos, vel;
    size_t score;
} Player;


void game_init();
void game_update();
void game_draw(GContext* ctx, Layer* layer);
void cleanup();

#endif