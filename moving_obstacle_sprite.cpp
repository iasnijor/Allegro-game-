/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "world.h"
#include "moving_obstacle_sprite.h"
#include "image_library.h"
#include "image_sequence.h"

namespace csis3700 {
  moving_obstacle_sprite::moving_obstacle_sprite(world *w,float initial_x, float initial_y) : phys_sprite(initial_x, initial_y) {
      
      this->w = w;
      obs->set_scale(.5);
      image_library *i1= image_library::get();
      obs->add_image(i1->get("Kunai.png"),.2);
      set_velocity(vec2d(-500,0));
      set_image_sequence(obs);
     
     
  }
      void  moving_obstacle_sprite::advance_by_time(double dt){
          if (w->is_game_over()) set_velocity(vec2d(0,0));
           phys_sprite::advance_by_time(dt);
      }
 

 
   void  moving_obstacle_sprite::resolve(const collision& collision, sprite* other) {
    
  }
   


}






















