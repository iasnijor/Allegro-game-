#include <cmath>
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

#include "world.h"

using namespace std;
using namespace csis3700;

const float FPS = 60;

const size_t WIDTH = 900;
const size_t HEIGHT = 900;

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *image = NULL;
     ALLEGRO_SAMPLE *sample=NULL;
    if (!al_init()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    if (!al_install_keyboard()) {
        cerr << "Failed to install keyboard." << endl;
        exit(1);
    }
    if (!al_install_mouse()) {
        cerr << "Failed to install mouse." << endl;
        exit(1);
    }
    if (!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
 if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }
    if (!al_reserve_samples(5)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
  /*   sample = al_load_sample( "1.wav" );

   if (!sample){
      printf( "Audio clip sample not loaded!\n" ); 
      return -1;
   }*/
    if (!al_init_font_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_font_addon!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;

    }
    if (!al_init_ttf_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_ttf_addon!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    display = al_create_display(900, 900);

    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

    if (!event_queue) {
        al_show_native_message_box(display, "Error", "Error", "Failed to create event queue!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);
    csis3700::world world;
 //al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    ALLEGRO_EVENT ev;
    do {
      
            al_wait_for_event(event_queue, &ev);
            world.advance_by_time(1 / FPS);
            world.draw();



            al_flip_display();
        
   
    } while (!world.should_exit() && ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE);

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    


    return 0;
}
































