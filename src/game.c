#include <pebble.h>
#include "game.h"
    
#define DT_MS 50
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
    p->pos.x += by_x;
    p->pos.y += by_y;
}

/*
* Initializes game
*/
void game_init() {
    create_player();
    app_timer_register(DT_MS, game_update, NULL);
}


void game_update() {
    move_player(player, 1, 0);
    app_timer_register(DT_MS, game_update, NULL);
}

void draw_player(Player* p, Layer* layer, GContext* ctx) {
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_fill_circle(ctx, GPoint(p->pos.x, p->pos.y),
                         CIRCLE_RADIUS);
    graphics_context_set_fill_color(ctx, GColorBlack);
}

void game_draw(Layer* layer, GContext* ctx) {
    draw_player(player, layer, ctx);
}

void game_cleanup() {
   free(player);
}