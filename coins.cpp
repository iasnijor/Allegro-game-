/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "coins.h"
#include "image_library.h"
#include "image_sequence.h"

namespace csis3700 {
 coins::coins(float initial_x, float initial_y, ALLEGRO_BITMAP *image) : sprite(initial_x, initial_y) {
      coin->set_scale(.05);
     coin->add_image(image,0);
     set_image_sequence(coin);
     isCoin = true;
     
  }

  vec2d coins::get_velocity() const {
    return vec2d(0,0);
  }

  void coins::set_velocity(const vec2d& v) {
    assert(false);
  }
   void coins::resolve(const collision& collision, sprite* other) {
    
  }
     bool coins::is_coin() const{
         return true;
     }
   
   


}












