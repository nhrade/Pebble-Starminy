#include <pebble.h>
#include "game.h"
#define CIRCLE_RADIUS 7
#define INITIAL_POINT (Vector2) {50.0, 50.0}

static void create_player() {
    if(player == NULL) {
        player = malloc(sizeof(Player));
    } 
    
    player->pos = INITIAL_POINT;
    player->vel = (Vector2) {0.0, 0.0};
    player->score = 0;
    player->lives = 0;
}

static void move_player(Player* p, double by_x, double by_y) {
    
}

/*
* Initializes game
*/
void game_init() {
    create_player();
}


void game_update() {
   
}

void draw_player(Player* p, Layer* layer, GContext* ctx) {
    graphics_fill_circle(ctx, GPoint(p->pos.x, p->pos.y),
                         CIRCLE_RADIUS);
}

void game_draw(Layer* layer, GContext* ctx) {
    draw_player(player, layer, ctx);
}

void game_cleanup() {
   free(player);
}