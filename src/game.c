#include <pebble.h>
#include <stdio.h>
#include "game.h"
#include "mine.h"
#include "accelerometer_manager.h"
#include <math.h>
#define DT_MS 50
#define ACCEL_CONSTANT 0.01
#define V_MAX 2
#define MAX_MINES 6
#define MAX_LIVES 3
#define CIRCLE_RADIUS 7
#define INITIAL_POINT (Vector2) {layer_get_bounds(window_layer).size.w/2, \
    layer_get_bounds(window_layer).size.h/2}


static GBitmap* heart_image;
static Player* player;
static BitmapLayer* heart_layers[MAX_LIVES];
static GBitmap* mine_image;
static Mine mines[6];

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
    player->lives = MAX_LIVES;
}

static void move_player(Player* p, double by_x, double by_y) {
    p->pos.x += by_x;
    p->pos.y += by_y;
    Vector2 v_slowed = (Vector2) {p->vel.x*p->slowdown_speed, p->vel.y*p->slowdown_speed};
    p->vel = v_slowed;
}

static void clear_screen(GContext* ctx) {
    graphics_context_set_fill_color(ctx, GColorClear);
    graphics_fill_rect(ctx, layer_get_bounds(window_layer),0,0);
}

static void apply_change(Player* p, AccelData data) {
    p->vel.x += data.x * ACCEL_CONSTANT;
    p->vel.y += -(data.y * ACCEL_CONSTANT);
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
    
    if((heart_image = gbitmap_create_with_resource(
        RESOURCE_ID_LIFE_SCORE_IMAGE)) == NULL) {
        APP_LOG(APP_LOG_LEVEL_ERROR, "Couldn't load heart image!");
    } 
    if((mine_image = gbitmap_create_with_resource(RESOURCE_ID_MINE_IMAGE)) == NULL) {
        APP_LOG(APP_LOG_LEVEL_ERROR, "Couldn't load mine image!");    
    }
    
    create_player();
    for(int i = 0; i < MAX_LIVES; i++) {
        heart_layers[i] = bitmap_layer_create(GRect(12 * i, 0, 17, 17));
        bitmap_layer_set_bitmap(heart_layers[i], heart_image);
        bitmap_layer_set_compositing_mode(heart_layers[i], GCompOpAnd);
        layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(heart_layers[i]));
    
    }
    app_timer_register(DT_MS, game_update, NULL);
    
    
    accel_data_service_subscribe(0, NULL);
}

static void draw_lives() {
    
}

static void bounds_check(Player* p) {
    GRect bounds = layer_get_bounds(window_layer);
    if(p->pos.x > (bounds.size.w - 5))
        p->pos.x = bounds.size.w - 5;
    else if(p->pos.y > (bounds.size.h - 5))
        p->pos.y = bounds.size.h - 5;
    else if(p->pos.x < 5)
        p->pos.x = 5;
    else if(p->pos.y < 5)
        p->pos.y = 5;
}

void game_update() {
    player_update(player);
    layer_mark_dirty(window_layer);
    app_timer_register(DT_MS, game_update, NULL);
    
    AccelData data;
    get_accel_data(&data);
    apply_change(player, data);
    bounds_check(player);
    //#ifdef DEBUG_APP
    //APP_LOG(APP_LOG_LEVEL_INFO, "X: %d Y: %d Z: %d", data->x, data->y, data->z);
    //#endif 
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
    gbitmap_destroy(heart_image);
    for(int i = 0; i < MAX_LIVES; i++){
        bitmap_layer_destroy(heart_layers[i]);
    }
    accel_data_service_unsubscribe();
}