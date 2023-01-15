/**
 * \class Enemy
 * Presents enemys view as a mad packmen witch running across the game field and snaps its mouth.
 * Based on Actor class.
*/

#pragma once
#include "Actor.hpp"
#include <SFML/Graphics.hpp>

class Enemy : public Actor
{
public:
    Enemy (unsigned int frame_limit, sf::Vector2f & position, sf::Vector2f & size, sf::Vector2f & velocity);
    ~Enemy () {};
};