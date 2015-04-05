#include <pebble.h>
#include "mine.h"
#include "game.h"

Mine* create_mine(GBitmap* image) {
    Mine* m = malloc(sizeof(Mine));
    m->pos = (Vector2) {RAND(WINDOW_WIDTH), RAND(WINDOW_HEIGHT)};
    m->layer = bitmap_layer_create(GRect(m->pos.x, m->pos.y, 25, 25));
    m->time_off = (double) (((double) (rand() % 400)) / 100.0);
    double center_y = m->pos.y;
    m->vel = (Vector2) {RAND(1)+1, 0};
    bitmap_layer_set_bitmap(m->layer, image);
    layer_add_child(window_get_root_layer(main_window), bitmap_layer_get_layer(m->layer));
    return m;
}

void destroy_mine(Mine* mine) {
    bitmap_layer_destroy(mine->layer);
    free(mine);
}

void update_mine(Mine* mine) {
    
}