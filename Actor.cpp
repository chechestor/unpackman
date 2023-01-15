#include "Actor.hpp"
#include "Calcs.hpp"

/// @brief Update the actor state
/// @param window Pointer to render game window
void Actor::update(sf::RenderWindow * window)
{
    //new positions
    this->position += this->frame_velocity;
    if ( (this->position.x >= window->getSize().x) && (velocity.x >0) )  {this->set_velocity( -velocity.x, velocity.y);}
    if ( (this->position.x <=0 ) && (velocity.x < 0) )  {this->set_velocity( -velocity.x, velocity.y);}

    if ( (this->position.y >= window->getSize().y) && (velocity.y >0) )  {this->set_velocity( velocity.x, -velocity.y);}
    if ( (this->position.y <=0 ) && (velocity.y < 0) )  {this->set_velocity( velocity.x, -velocity.y);}

    this->sprite_update();
}

/// @brief Draw actor on game field
/// @param window Pointer to render game window
void Actor::render (sf::RenderWindow * window)
{
    this->sprite_render(window);
}

/// @brief Set a new position of object on game field
/// The position relative to the upper left corner of the game window/
/// The vector points to the center of the actor.
/// @param new_position New vector position
void Actor::set_position(const sf::Vector2f & new_position)
{
    this->position = new_position;
}

/// @brief Set a new position of object on game field
/// The position relative to the upper left corner of the game window/
/// The vector points to the center of the actor.
/// @param new_position New vector position
void Actor::set_position(const sf::Vector2i & new_position)
{
    this->position = sf::Vector2f(new_position.x, new_position.y);
}

/// @brief Set a new X*Y actor dimensions
/// @param new_size New X*Y dimensions
void Actor::set_size(sf::Vector2f & new_size)
{
    this->size = new_size;
}

/// @brief Set a new value for the object's speed
/// @param new_velocity New vX * vY velocity vector
void Actor::set_velocity(sf::Vector2f & new_velocity)
{
    this->velocity = new_velocity;
    this->frame_velocity = sf::Vector2f ( this->velocity.x / this->frame_limit, this->velocity.y / this->frame_limit );
}

/// @brief Set a new value for the object's speed
/// @param new_velocity New vX * vY velocity vector
void Actor::set_velocity(float vX, float vY)
{
    this->velocity = sf::Vector2f(vX, vY);
    this->frame_velocity = sf::Vector2f ( this->velocity.x / this->frame_limit, this->velocity.y / this->frame_limit );
}

/// @brief Gets the current position of the object on game field
/// The position relative to the upper left corner of the game window/
/// The vector points to the center of the actor.
/// @return current position
sf::Vector2f Actor::get_position()
{
    return this->position;
}

/// @brief Gets an X*Y actor dimensions
/// @return X*Y dimensions in a vector
sf::Vector2f Actor::get_size()
{
    return this->size;
}

/// @brief Gets an object's velocity
/// @return vX * vY velocity vector
sf::Vector2f Actor::get_velocity()
{
    return this->velocity;
}

/// @brief Sets a framerate for the game
/// @param frame_limit game framerate. Frames per second.
void Actor::set_frame_limit(unsigned int frame_limit)
{
    this->frame_limit = frame_limit;
    this->frame_velocity = sf::Vector2f ( this->velocity.x / this->frame_limit, this->velocity.x / this->frame_limit );
}

/// @brief Gets the games framerate
/// @return game framerate. Frames per second.
unsigned int Actor::get_frame_limit()
{
    return this->frame_limit;
}

/// @brief Sets sprite image for actor
/// @param texture_path path to PNG file with sprite texture
/// @param sprites_per_second Frequency of sprite change per second
void Actor::init_sprite(std::string texture_path, float sprites_per_second)
{
    this->texture.loadFromFile(texture_path);
    this->sprite_height = this->texture.getSize().y;  //
    this->sprites_sheet_qty = this->texture.getSize().x / this->sprite_height;
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(this->get_size().x/this->get_size().x, this->get_size().x/this->get_size().y);
    this->current_sprite_frame = rand() % this->sprites_sheet_qty;
    this->set_sprites_per_second(sprites_per_second);
}

/// @brief Sets a new frequency of sprite changes
/// @param sprites_per_second Frequency of sprite change per second
void Actor::set_sprites_per_second(float sprites_per_second)
{
    this->sprites_per_second = sprites_per_second;
    unsigned int sp = this->get_frame_limit();
    this->sprites_renew_frame_cnt_max = sp / this->sprites_per_second;  // counter for frames betwin stprite_renews
    this->sprites_renew_frame_cnt = rand() % sprites_renew_frame_cnt_max;
}

/// @brief Calculate new internal state for actor
void Actor::sprite_update()
{
    //renew sprite
    this->sprites_renew_frame_cnt ++;
    if (this->sprites_renew_frame_cnt > this->sprites_renew_frame_cnt_max)
    {
        this->sprites_renew_frame_cnt = 0;
        this->current_sprite_frame ++;
        if (this->current_sprite_frame >= sprites_sheet_qty)
        {
            this->current_sprite_frame = 0;
        }
    }
}

/// @brief Draw actor on game field
/// @param render_window Pointer to game window
void Actor::sprite_render(sf::RenderWindow * render_window)
{

    auto size = sf::Vector2f(this->get_size().x, this->get_size().y);
    this->sprite.setScale(this->get_size() / float(this->sprite_height));
    
    this->sprite.setTextureRect(sf::IntRect(this->sprite_height * this->current_sprite_frame, 0, this->sprite_height, this->sprite_height));

    sf::Vector2f angle_velocity_ra_rad = xy_to_ra (this->get_velocity());
    auto pos = get_centered_after_rotate(this->position, (angle_velocity_ra_rad.y), this->get_size());
    this->sprite.setPosition(pos);
    this->sprite.setRotation(angle_velocity_ra_rad.y * 180.0 / M_PI);
    
    render_window->draw(this->sprite);
}
