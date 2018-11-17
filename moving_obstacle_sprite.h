/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   moving_obstacle.h
 * Author: Rojen
 *
 * Created on April 28, 2018, 7:23 PM
 */

#ifndef MOVING_OBSTACLE_SPRITE_H
#define MOVING_OBSTACLE_SPRITE_H
#include "sprite.h"
#include "phys_sprite.h"
#include "world.h"
namespace csis3700 {

  /**
   * obstruction_sprites don't typically move and when they
   * participate in a collision they are unimpacted by it. They
   * typically render themslves as a single, static bitmap.
   */
  class moving_obstacle_sprite : public phys_sprite {
  public:
    moving_obstacle_sprite(world *w,float initial_x, float initial_y);
 /*   virtual void set_velocity(const vec2d& v);
    virtual vec2d get_velocity() const;*/
    virtual void resolve(const collision& collision, sprite* other);
      virtual void advance_by_time(double dt);
  private :
      world *w;
       image_sequence *obs = new image_sequence();
       
      
  };
}


#endif /* MOVING_OBSTACLE_H */












