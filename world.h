#ifndef __CDS_WORLD_H
#define __CDS_WORLD_H

#include "allegro5/allegro.h"
#include "sprite.h"
#include "player_sprite.h"
#include"collision.h"
#include <vector>
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"




namespace csis3700 {
    class player_sprite;
  class world {
  public:
    /**
     * Construct the world. The display is passed in simply to make it
     * possible to modify options or access the backbuffer. DO NOT
     * store the display in an instance variable. DO NOT start drawing
     * on the screen. Just load bitmaps etc.
     */
    world();

    /**
     * Free any resources being used by the world.
     */
    ~world();

    /**
     * Block the copy constructor.  Worlds should not be copied to
     * just assert(false)
     */
    world(const world& other);

    /**
     * Block operator =.  Worlds should not be assigned.
     */
    world& operator =(const world& other);
 
    /**
     * Update the state of the world based on the event ev.
     */
    void handle_event(ALLEGRO_EVENT ev);

    /**
     * Advance the state of the world forward by the specified time.
     */
    void advance_by_time(double dt);

    /**
     * Draw the world. Note that the display variable is passed only
     * because it might be needed to switch the target bitmap back to
     * the backbuffer.
     */
    void draw();

    /**
     * Return true iff game is over and window should close
     */
    bool should_exit();
    sprite * get_obs();
    void player_killed();
    bool is_game_over();
     void increment_coin(sprite * other);
  private:
        ALLEGRO_DISPLAY *display;
        ALLEGRO_BITMAP *background;
        ALLEGRO_BITMAP *obstacle;
        ALLEGRO_BITMAP *obstacle2;
         ALLEGRO_BITMAP *obstacle3;
        ALLEGRO_BITMAP *coin;
        //level l;
        void resolve_collisions();
        void handle_collisions(std::vector<collision>& c);
        player_sprite *player;
        std::vector<sprite*> sprites;
        void create_sprites();
        void create_sprites2();
        float x;
        bool isOver;
         ALLEGRO_FONT *font;
         int coin_collector;
         ALLEGRO_FONT *font2;
         ALLEGRO_SAMPLE *game = NULL;
         ALLEGRO_SAMPLE_INSTANCE *song_instance=NULL;
         int level ;
       
  };
}

#endif /* WORLD_H */
