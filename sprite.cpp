#include "sprite.h"
#include <allegro5/allegro_color.h>
#include <iostream>
#include <cmath>
using namespace std;

namespace csis3700 {

    sprite::sprite(float initial_x, float initial_y) {
        position = vec2d(initial_x, initial_y);
        time = 0;
    }

    void sprite::set_image_sequence(image_sequence *s) {
        sequence = s;
    }

    sprite::~sprite() {
    }

    int sprite::get_width() const {
        return sequence->get_width();
    }

    int sprite::get_height() const {
        return sequence->get_height();
    }

    float sprite::get_x() const {
        return position.get_x();
    }

    float sprite::get_y() const {
        return position.get_y();
    }

    void sprite::draw() {
        sequence->draw(time, get_x(), get_y());
    }

    rectangle sprite::bounding_box() const {
        return rectangle(position, get_width(), get_height());
    }

    rectangle sprite::collision_rectangle(const sprite& other) const {
        return bounding_box().intersection(other.bounding_box());
    }

    bool sprite::collides_with(const sprite& other) const {
        if (collision_rectangle(other).is_degenerate()) return false;
        else 
            return true;
       


        /*
        int top = position.get_y() > other.get_y() ? position.get_y() : other.position.get_y();
        int bottom = position.get_y() + al_get_bitmap_height(sequence->get_current_image()) > other.get_y() + al_get_bitmap_height(other.sequence->get_current_image()) ? other.get_y() + al_get_bitmap_height(other.sequence->get_current_image()) : position.get_y() + al_get_bitmap_height(sequence->get_current_image());
        int left = position.get_x() > other.get_x() ? position.get_x() : other.get_x();
        int right = position.get_x() + al_get_bitmap_width(sequence->get_current_image()) > other.get_x() + al_get_bitmap_width(other.sequence->get_current_image()) ? other.get_x() + al_get_bitmap_width(other.sequence->get_current_image()) : position.get_x() + al_get_bitmap_width(sequence->get_current_image());
 
         al_lock_bitmap(sequence->get_current_image(), al_get_bitmap_format(sequence->get_current_image()), ALLEGRO_LOCK_READONLY);
        al_lock_bitmap(other.sequence->get_current_image(), al_get_bitmap_format(other.sequence->get_current_image()), ALLEGRO_LOCK_READONLY);
         ALLEGRO_COLOR color;
          ALLEGRO_COLOR color2;
        for (int i = top; i < bottom; i++) {
            for (int j = left; j < right; j++) {
                color = al_get_pixel(sequence->get_current_image(), abs(j - position.get_x()),abs( i - position.get_y()));
                  color2 = al_get_pixel(other.sequence->get_current_image(),abs( j - other.get_x()),abs( i - other.get_y()));
                if (color.a != 0 && color2.a != 0) {
                    cout << "row: " << i << "  col: " << j << endl;
                    al_unlock_bitmap(sequence->get_current_image());
                    al_unlock_bitmap(other.sequence->get_current_image());
                    return true;
                }


            }
        }
        al_unlock_bitmap(sequence->get_current_image());
         al_unlock_bitmap(other.sequence->get_current_image());
        return false;
*/
    }

    void sprite::advance_by_time(double dt) {
        time += dt;
    }

    vec2d sprite::get_position() const {
        return position;
    }

    void sprite::set_position(vec2d p) {
        position = p;
    }

    bool sprite::is_player() const {
        return false;
    }

    bool sprite::is_coin()const {
        return false;
    }

}
