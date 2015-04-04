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
}


void game_update() {
    
}

void game_draw(GContext* ctx, Layer* layer) {
    
}

void cleanup() {
   free(player);
}