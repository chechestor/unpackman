/**
 * \class Cursor
 * Presents cursor view as a little ghost.
 * Uses class Actor for draw sprites.
*/

#pragma once
#include "Actor.hpp"
#include <SFML/Graphics.hpp>

class Cursor : public Actor
{
public:
    Cursor (unsigned int frame_limit, unsigned int radius_pxl);
    ~Cursor () {};
    void update(sf::RenderWindow *);
    void render(sf::RenderWindow *);
};