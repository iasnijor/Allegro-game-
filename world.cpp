#include "world.h"
#include <cassert>
#include <algorithm>
#include "sprite.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "player_sprite.h"
#include "obstruction_sprite.h"
#include "collision.h"
#include "image_library.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

#include "coins.h"
#include "moving_obstacle_sprite.h"

using namespace std;

namespace csis3700 {

    const float gravity_acceleration = 600;

    void free_sprite(sprite* s) {
        delete s;
    }

    world::world() {
        /*level l;
         sprites= l.get_sprites()*/
        create_sprites();
        background = image_library::get()->get("bg.png");
        isOver = false;


        font = al_load_ttf_font("arial.ttf", 80, 0);
        if (!font) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load font!",
                    NULL, ALLEGRO_MESSAGEBOX_ERROR);
            return;
        }
         font2 = al_load_ttf_font("arial.ttf", 36, 0);
        if (!font2) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load font!",
                    NULL, ALLEGRO_MESSAGEBOX_ERROR);
            return;
        }
         game = al_load_sample("game.wav");
        if (!game) {
        printf( "Audio clip sample not loaded!\n" ); 
         return ;
        }
         
         song_instance = al_create_sample_instance(game);
         al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
         al_attach_sample_instance_to_mixer(song_instance,al_get_default_mixer());
         
         

        coin_collector = 0;
    }

    void world::create_sprites() {
        sprite *player = new player_sprite(this, 250, 650,500);
        obstacle = image_library::get()->get("obs.png");
        obstacle2 = image_library::get()->get("obs2.png");
        coin = image_library::get()->get("coin.png");
        
        level=1;
        
        int position = 2000;
        sprites.push_back(player);

        for (int i = 0; i < 50; i++) {
            sprite *obstruction = new obstruction_sprite(position, 660, obstacle);
            sprite *obstruction2 = new obstruction_sprite(position + 1000, 620, obstacle2);
            sprite *collect_coin = new coins(position + 500, 640, coin);
            sprites.push_back(obstruction);
            sprites.push_back(obstruction2);
            sprites.push_back(collect_coin);
            position += rand()%1000 + 1800;
        }
    }
        
        void world::create_sprites2() {
             sprite *player = new player_sprite(this, 250, 650,1000);
        obstacle = image_library::get()->get("obs.png");
        obstacle2 = image_library::get()->get("obs2.png");
        coin = image_library::get()->get("coin.png");
        
        level=2;
        
        int position = 2000;
      
        sprites.push_back(player);

        for (int i = 0; i < 50; i++) {
            sprite *obstruction = new obstruction_sprite(position, 660, obstacle);
            sprite *obstruction2 = new obstruction_sprite(position + 1000, 620, obstacle2);
            sprite *collect_coin = new coins(position + 500, 640, coin);
              sprite *collect_coins = new coins(position + 560, 640, coin);
            sprite *moving_obstacle = new moving_obstacle_sprite(this,position+1500,660);
            sprites.push_back(obstruction);
            sprites.push_back(obstruction2);
            sprites.push_back(collect_coin);
            sprites.push_back(collect_coins);
            sprites.push_back(moving_obstacle);
            position += rand()%1000 +1000;
            
            
        }
        }

    

    world::world(const world& other) {
        assert(false); // do not copy worlds
    }

    world& world::operator=(const world& other) {
        assert(false); // do not assign worlds
    }

    world::~world() {
        for_each(sprites.begin(), sprites.end(), free_sprite);
        sprites.clear();
    }

    void world::handle_event(ALLEGRO_EVENT ev) {
    }

    void world::handle_collisions(vector<collision>& c) {
  
        for (auto it = c.begin(); it != c.end(); ++it)
            it->resolve();
    }

    void world::resolve_collisions() {
        vector<collision> collisions;
        //for(auto i=sprites.begin(); i != sprites.end(); ++i)
        auto i = sprites.begin();
        for (auto j = i + 1; j != sprites.end(); j++)
            if ((*i)->collides_with(**j))
                collisions.push_back(collision(*i, *j));
        //if (collisions.size()>0)
        handle_collisions(collisions);

    }

    void world::advance_by_time(double dt) {
        for (vector<sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
            (*it)->advance_by_time(dt);
        resolve_collisions();
    }

    void world::draw() {
          
        
        
        if (coin_collector >3 && level==1){
            level =2;
                 for_each(sprites.begin(), sprites.end(), free_sprite);
                    sprites.clear();
            create_sprites2();
                    
        }
        al_play_sample_instance(song_instance);
         
        ALLEGRO_TRANSFORM t;
        sprite* obs = get_obs();
        al_identity_transform(&t);
        if (obs != nullptr)
            al_translate_transform(&t, -obs->get_x() + 50, 0);
        al_use_transform(&t);
        al_clear_to_color(al_map_rgb(255, 255, 255));
        int background_width = al_get_bitmap_width(background);
        x = sprites.front()->get_x();
        int ninja = x / background_width;
       
        al_draw_bitmap(background, -background_width + ninja*background_width, 0, 0);
        al_draw_bitmap(background, ninja*background_width, 0, 0);
        al_draw_bitmap(background, background_width + ninja*background_width, 0, 0);

        for (auto it = sprites.begin(); it != sprites.end(); ++it)
            (*it)->draw();
        int score = coin_collector;
        if(!isOver){
         al_draw_textf(font2, al_map_rgb(255, 255, 255), x + 600, 90, 0, "Score: %i", score);    
         al_draw_textf(font2, al_map_rgb(255, 255, 255), x , 90, 0, "Level: %i", level);   
        }
       
        if (isOver) {
            al_draw_text(font, al_map_rgb(255, 255, 255), x + 100, 250, 0, "Game Over");
            al_draw_textf(font, al_map_rgb(255, 255, 255), x + 120, 350, 0, "Score: %i", score);
        }
    }

    void world::increment_coin(sprite * other) {
        coin_collector++;

        sprites.erase(std::remove(sprites.begin(), sprites.end(),other), sprites.end());
          
   }

      
    

    bool world::should_exit() {
        return false;
    }
    bool world:: is_game_over(){
        return isOver;
    }
    sprite* world::get_obs() {
        return sprites.front();
    }

    void world::player_killed() {
    
        isOver = true;
        //al_stop_sample(game);
        
    }
}
