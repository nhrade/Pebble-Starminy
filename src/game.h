#ifndef GAME_H_
#define GAME_H_
#include <pebble.h>
#define RAND(n) rand() % n
#define WINDOW_WIDTH layer_get_bounds(window_layer).size.w
#define WINDOW_HEIGHT layer_get_bounds(window_layer).size.h

Layer* window_layer;
Window* main_window;

typedef struct Vector2_S {
   double x, y;  
} Vector2;
    
typedef struct Player_S {
    Vector2 pos, vel, acc;
    double slowdown_speed;
    size_t score, lives;
} Player;

void game_init(Layer* layer, Window* window);
void game_update();
void game_draw(Layer* layer, GContext* ctx);
void game_cleanup(void);

#endif