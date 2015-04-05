#include <pebble.h>
#include "game.h"
    
#define DT_MS 50
#define CIRCLE_RADIUS 7
#define INITIAL_POINT (Vector2) {50.0, 50.0}

static Layer* window_layer;
static Window* main_window;
static void create_player(void) {
    if(player == NULL) {
        player = malloc(sizeof(Player));
    } 
    
    player->pos = INITIAL_POINT;
    player->vel = (Vector2) {1.0, 1.0};
    player->score = 0;
    player->lives = 0;
}

static void move_player(Player* p, double by_x, double by_y) {
    p->pos.x += by_x;
    p->pos.y += by_y;
}

static void clear_screen(GContext* ctx) {
    graphics_context_set_fill_color(ctx, GColorClear);
    graphics_fill_rect(ctx, layer_get_bounds(window_layer),0,0);
}

static void player_update(Player* p) {
    move_player(player, p->vel.x, p->vel.y);
}

/*
* Initializes game
*/
void game_init(Layer* layer, Window* window) {
    window_layer = layer;
    main_window = window;
		window_set_background_color(main_window, GColorClear);
    create_player();
    app_timer_register(DT_MS, game_update, NULL);
}


void game_update() {
    player_update(player);
    layer_mark_dirty(window_layer);
    app_timer_register(DT_MS, game_update, NULL);
}

void draw_player(Player* p, Layer* layer, GContext* ctx) {
    //clear_screen(ctx);
    psleep(DT_MS);
	
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_circle(ctx, GPoint(p->pos.x, p->pos.y),
                         CIRCLE_RADIUS); 
}

void game_draw(Layer* layer, GContext* ctx) {
	  clear_screen(ctx);  	
		draw_player(player, layer, ctx);	
}

void game_cleanup(void) {
   free(player);
}