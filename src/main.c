#include <pebble.h>
#include "acceleration.h"
#include "game.h"

static Window *s_main_window;
static Layer* window_layer;

/*
static void compass_heading_handler(CompassHeadingData heading_data) {
    app_log(1, "main.c", 21, "Heading: %d", (int) TRIGANGLE_TO_DEG(heading_data.true_heading));
}*/

static void main_window_load(Window *window) {
    window_layer = window_get_root_layer(window);
    layer_set_update_proc(window_layer, game_draw);

    
}

static void main_window_unload(Window *window) {
    window_destroy(window);
}


static void init() {
    s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload
    });
    // Show the Window on the watch, with animated=true
    window_stack_push(s_main_window, true);
    game_init();
}



int main(void) {
    init();
    app_event_loop();
    game_cleanup();
}
