#include <pebble.h>
#include "acceleration.h"
#include "game.h"
    

static Window *s_main_window;
static TextLayer* compass_layer;


/*
static void compass_heading_handler(CompassHeadingData heading_data) {
    app_log(1, "main.c", 21, "Heading: %d", (int) TRIGANGLE_TO_DEG(heading_data.true_heading));
}*/

static void main_window_load(Window *window) {
   
    compass_layer = text_layer_create(GRect(00, 55, 144, 50));
    text_layer_set_background_color(compass_layer, GColorClear);
    text_layer_set_text_color(compass_layer, GColorBlack);
    //CompassHeadingData data;
    //compass_service_peek(&data);
    //
    text_layer_set_text(compass_layer, "0");
    text_layer_set_font(compass_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
    text_layer_set_text_alignment(compass_layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(compass_layer));
}

static void main_window_unload(Window *window) {
    text_layer_destroy(compass_layer);
}


static void init() {
  // Create main Window element and assign to pointer
    s_main_window = window_create();
    //accel_tap_service_subscribe(tap_handler);
    //compass_service_subscribe(compass_heading_handler);
    
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload
    });

    // Show the Window on the watch, with animated=true
    window_stack_push(s_main_window, true);
}

static void deinit() {
    window_destroy(s_main_window);
}


int main(void) {
    init();
    app_event_loop();
    deinit();
}
