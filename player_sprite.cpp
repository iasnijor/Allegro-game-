#include "player_sprite.h"
#include "image_library.h"
#include "image_sequence.h"
#include "keyboard_manager.h"
#include "vec2d.h"
#include "collision.h"
#include <cmath>
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
using namespace std;

namespace csis3700 {

    player_sprite::player_sprite(world * w, float initial_x, float initial_y,float velocity_x) :
    phys_sprite(initial_x, initial_y) {
        theWorld = w;
        create_image_sequence();
        alive = true;
        up = al_load_sample("up.wav");
        if (!up) {
        printf( "Audio clip sample not loaded!\n" ); 
         return ;
        }
         fall = al_load_sample("fall.wav");
        if (!fall) {
        printf( "Audio clip sample not loaded!\n" ); 
         return ;
        }
          sliding = al_load_sample("slide.wav");
        if (!sliding) {
        printf( "Audio clip sample not loaded!\n" ); 
         return ;
        }
          set_velocity(vec2d(velocity_x, 0));

    }

    void player_sprite::create_image_sequence() {

        s->set_scale(.3);
        image_library *il = image_library::get();
        s->add_image(il->get("Run__000.png"), 0);
        s->add_image(il->get("Run__003.png"), 0.1);
        s->add_image(il->get("Run__005.png"), 0.1);
        s->add_image(il->get("Run__007.png"), 0.1);\
        s->add_image(il->get("Run__009.png"), 0.1);
        set_image_sequence(s);

        jump->set_scale(.3);
        image_library *il1 = image_library::get();
        jump->add_image(il1->get("Jump__000.png"), .2);
        jump->add_image(il1->get("Jump__003.png"), .2);
        jump->add_image(il1->get("Jump__004.png"), .3);
        jump->add_image(il1->get("Jump__005.png"), .2);
        jump->add_image(il1->get("Jump__006.png"), .2);
        jump->add_image(il1->get("Jump__007.png"), .2);\
        jump->add_image(il1->get("Jump__008.png"), .2);
        jump->add_image(il1->get("Jump__009.png"), .2);

        slide->set_scale(.3);
        image_library *il2 = image_library::get();
        slide->add_image(il2->get("Slide__000.png"), .2);
        slide->add_image(il2->get("Slide__003.png"), .4);
        slide->add_image(il2->get("Slide__004.png"), .4);
        slide->add_image(il2->get("Slide__005.png"), .4);
        slide->add_image(il2->get("Slide__006.png"), .7);
        slide->add_image(il2->get("Slide__007.png"), .5);\
        slide->add_image(il2->get("Slide__008.png"), .5);
        slide->add_image(il2->get("Slide__009.png"), .5);
       
        dead->set_scale(.3);
        image_library *il3 = image_library::get();
        dead->add_image(il3->get("Dead__007.png"), .2);
        
      
    }
    
     bool player_sprite::is_player() const {
    return true;
  }
     
    void player_sprite::advance_by_time(double dt) {
       
        if(alive){
        if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_UP) && get_y()==650) {
            set_velocity(vec2d(700, -550));
            set_acceleration(vec2d(0, 805));
            set_image_sequence(jump);
            al_play_sample(up,2.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
          
        } 
        else if (keyboard_manager::get()->is_key_down(ALLEGRO_KEY_DOWN)){
           
            set_velocity(vec2d(700,650 ));
            set_acceleration(vec2d(0,800));
            if(get_y()>675){
                set_velocity(vec2d(700,0));
            }
            set_image_sequence(slide);
           al_play_sample(sliding,2.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
        }
            
           else if (get_y() > 650 ) {
             set_position(vec2d(get_x(),650));
            set_velocity(vec2d(700, 0));
              set_image_sequence(s);
      }
        }
              phys_sprite::advance_by_time(dt);
    }
    void player_sprite::resolve(const collision& collision, sprite *other) {
        if (other->is_coin()){
            theWorld->increment_coin(other);
           
        }
        else {
          
            if(alive)
            al_play_sample(fall,2.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
              alive = false;
       theWorld->player_killed();
    set_image_sequence(dead);
    set_velocity(vec2d(0,0));
    set_position(vec2d(get_x(),650));
     
        }
      
  }

}
