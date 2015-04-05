#include <pebble.h>

#include "game.h"

static Window *s_main_window;
static Layer* window_layer;

static void main_window_load(Window *window) {
    window_layer = window_get_root_layer(window);
    layer_set_update_proc(window_layer, game_draw);
}

static void main_window_unload(Window *window) {
    window_destroy(window);
}

static void init(void) {
    s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload
    });
    // Show the Window on the watch, with animated=true
    window_stack_push(s_main_window, true);
    game_init(window_layer, s_main_window);
}

int main(void) {
		srand (time(NULL));
    init();
    app_event_loop();
    game_cleanup();
}
