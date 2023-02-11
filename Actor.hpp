/**
 * \class Actor
 * Base class for game actors.
 * Actor's view is based on a linear PNG picture sprite sheet (horizontal extended)
 * Sprites changes periodicaly with defined friquency.
 * Class user should define followin parameters on init:
 * - size (x*Y) of actor
 * - vector velocity of actor (vX*vY)
 * - framerate
 * - sprite sheet image (PNG texture image)
 * - sprites change frequency
 * On each frame should call update() method for calculate new actor state.
 * On each frame should call render() method for draw actor on game field.
*/

#pragma once
#include <utility>
#include <chrono>
#include <SFML/Graphics.hpp>

class Actor
{
public:
    Actor (sf::RenderWindow *);
    ~Actor () {};
    void update ();
    void render ();

    void set_position (const sf::Vector2f &); 
    void set_position(const sf::Vector2i &);
    void set_size (sf::Vector2f &);
    void set_velocity (sf::Vector2f &);
    void set_velocity (float, float);
    sf::Vector2f get_position ();
    sf::Vector2f get_size ();
    sf::Vector2f get_velocity ();

    void set_frame_limit(unsigned int frame_limit);
    unsigned int get_frame_limit();

protected:
    sf::RenderWindow * window;
    sf::Vector2f position = sf::Vector2f(0,0);  ///< [X,Y] position on game field, pixels
    void init_sprite(std::string texture_path, float frames_per_second);
private:
    sf::Vector2f velocity = sf::Vector2f(100,100); ///< [vX,vY] current velocity on game field, pixels/s
    sf::Vector2f frame_velocity = sf::Vector2f(4.0f,4.0f); ///< [vX,vY] current velocity on game field, pixels/frame
    sf::Vector2f size = sf::Vector2f(10,10);  ///< [sX,sY] dimesions on game field, pixels
    unsigned int frame_limit = 25;  ///> default framelimit for actor

    // sprite context
    void set_sprites_per_second(float sprites_per_second);
    sf::Texture texture;  ///< texture for actor sprite
    sf::Sprite sprite;  ///< actors main sprite
    unsigned int sprite_height;  ///< height of sprites texture image
    float sprites_per_second;  /// sprites changes frequency (sprites changes per second)
    unsigned int sprites_renew_frame_cnt_max;  // max counter value for frames betwin stprite_renews
    unsigned int sprites_renew_frame_cnt;  // counter for frames betwin stprite_renews
    unsigned int sprites_sheet_qty;  // count of frames in linear sprite sheet image
    unsigned int current_sprite_frame;  // rurrent sprite frame from
    void sprite_update();
    void sprite_render(sf::RenderWindow * window);
 };