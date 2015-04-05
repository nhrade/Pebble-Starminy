#ifndef GAME_H_
#define GAME_H_
#include <pebble.h>


typedef struct Vector2_S {
   double x, y;  
} Vector2;
    
typedef struct Player_S {
    Vector2 pos, vel, acc;
    double slowdown_speed;
    size_t score, lives;
} Player;


static Player* player;

void game_init(Layer* layer, Window* window);
void game_update();
void game_draw(Layer* layer, GContext* ctx);
void game_cleanup(void);

#endif