#include "obstruction_sprite.h"
#include "image_library.h"
#include "image_sequence.h"

namespace csis3700 {
  obstruction_sprite::obstruction_sprite(float initial_x, float initial_y, ALLEGRO_BITMAP *image) : sprite(initial_x, initial_y) {
      obs->set_scale(.3);
     obs->add_image(image,0);
     set_image_sequence(obs);
     
     
  }

  vec2d obstruction_sprite::get_velocity() const {
    return vec2d(0,0);
  }

  void obstruction_sprite::set_velocity(const vec2d& v) {
    assert(false);
  }
   void obstruction_sprite::resolve(const collision& collision, sprite* other) {
    
  }
   


}
