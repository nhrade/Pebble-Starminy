#ifndef GAME_H_
#define GAME_H_
#include <pebble.h>


typedef struct Vector2_S {
   double x, y;  
} Vector2;
    
typedef struct Player_S {
    Vector2 pos, vel;
    size_t score;
} Player;


static Player* player;

bool game_init();
void game_update();
void game_draw(Layer* layer, GContext* ctx);
void game_cleanup();

#endif