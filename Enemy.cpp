#include "Enemy.hpp"
#include <math.h>
#include <utility>
#include "Calcs.hpp"

/// @brief Constructor for mad pacmen actor (enemy).
/// @param frame_limit Games framerate (frames per second)
/// @param position Current start position for pacmen. Vector(X,Y) in pixels.
/// @param size Size of pacmen. Vector(X,Y) in pixels.
/// @param velocity Vector of pacmens velocity. Vector(X,Y) in pixels per second.
Enemy::Enemy (unsigned int frame_limit, sf::Vector2f & position, sf::Vector2f & size, sf::Vector2f & velocity)
{
    this->set_frame_limit(frame_limit);
    this->set_position(position);
    this->set_size(size);
    this->set_velocity(velocity);
    this->init_sprite("./resources/Packman1.png" , 50);  //TODO: fix this magicnumbers
}
