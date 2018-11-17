#ifndef __CDS_COLLISION_H
#define __CDS_COLLISION_H

#include "sprite.h"
#include "rectangle.h"

namespace csis3700 {
  class collision {
  public:
    collision(sprite* p1, sprite* p2);
    sprite** get_participants();
    void create_sprites2();
    void resolve();
    rectangle collision_rectangle() const;
      

  private:
    sprite* participants[2];
  };
}
#endif /* COLLISION_H */
