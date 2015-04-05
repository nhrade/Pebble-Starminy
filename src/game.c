#include <pebble.h>
#include "game.h"
#include <math.h>
#define DT_MS 50
#define V_MAX 5
#define CIRCLE_RADIUS 7
#define INITIAL_POINT (Vector2) {50.0, 50.0}

static Layer* window_layer;
static Window* main_window;

static double get_mag(Vector2 v){
	double mag = sqrt(v.x*v.x+v.y*v.y);
	return mag;
}

static void create_player(void) {
    if(player == NULL) {
        player = malloc(sizeof(Player));
    } 
    
    player->pos = INITIAL_POINT;
    player->vel = (Vector2) {0.0, 0.0};
    player->acc = (Vector2) {0.0,0.0};
	player->slowdown_speed = 0.78;
    player->score = 0;
    player->lives = 0;
}


static void accelerate_player(Player* p, double by_x, double by_y) {
    double mag = get_mag(p->acc);  
	  p->vel.x += by_x/mag;
    p->vel.y += by_y/mag;
		p->acc = (Vector2) {0.0,0.0};
		double v_mag = get_mag(p->vel);
	  Vector2 v_normalized = (Vector2) {p->vel.x/v_mag, p->vel.y/v_mag};
		if(v_mag>V_MAX){
				p->vel = (Vector2) {v_normalized.x*V_MAX,v_normalized.x*V_MAX};
		}
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
    // accelerate_player(player, p->acc.x, p->acc.y);
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