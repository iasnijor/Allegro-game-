#ifndef __CDS_PLAYER_SPRITE_H
#define __CDS_PLAYER_SPRITE_H
#include "world.h"
#include "phys_sprite.h"
#include"image_sequence.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

namespace csis3700 {
       class world;
  class player_sprite : public phys_sprite {
   
  public:
    player_sprite(world *w,float initial_x=0, float initial_y=0,float velocity_x=0);
    virtual void advance_by_time(double dt);
    virtual bool is_player() const;
      virtual void resolve(const collision& collision, sprite* other);
  private:
        world *theWorld;
        void create_image_sequence();
        image_sequence *jump = new image_sequence();
        image_sequence *s = new image_sequence();
        image_sequence *slide = new image_sequence();
          image_sequence *dead = new image_sequence();
        bool alive;
        ALLEGRO_SAMPLE *up = NULL;
        ALLEGRO_SAMPLE *fall = NULL;
         ALLEGRO_SAMPLE *sliding = NULL;
        
        
        
  };
}


#endif /* PLAYER_SPRITE_H */
