#include <pebble.h>
#include "game.h"

/*
* Initializes game
* returns true if successful, false otherwise
*/
bool game_init() {
    player = malloc(sizeof(Player)); 
    if(player == NULL) {
        return false;
    }
    return true;
}


void game_update() {
   
}

void game_draw(Layer* layer, GContext* ctx) {
    GPoint p0 = GPoint(0, 0);
    GPoint p1 = GPoint(100, 100);
    graphics_context_set_stroke_color(ctx, GColorBlack);
    graphics_draw_line(ctx, p0, p1);
}

void game_cleanup() {
   free(player);
}