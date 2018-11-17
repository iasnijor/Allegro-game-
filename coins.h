/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   coins.h
 * Author: Rojen
 *
 * Created on April 24, 2018, 8:02 PM
 */

#ifndef COINS_H
#define COINS_H

#include "sprite.h"

namespace csis3700{
    class coins : public sprite{
         public:
        coins(float initial_x, float initial_y, ALLEGRO_BITMAP *image=NULL);
        virtual void set_velocity(const vec2d& v);
        virtual vec2d get_velocity() const;
        virtual void resolve(const collision& collision, sprite* other);
        virtual bool is_coin() const ;
        
  private :
       image_sequence *coin= new image_sequence();
       bool isCoin;
        
    };
}





#endif /* COINS_H */










