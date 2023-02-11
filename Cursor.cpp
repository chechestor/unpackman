#include "Cursor.hpp"

#include <SFML/Window.hpp>

/// @brief Constructor
/// @param frame_limit Frame rate of game 
/// @param radius_pxl Radius of cursor. In pixels
Cursor::Cursor (sf::RenderWindow * window, int frame_limit, unsigned int radius_pxl) : Actor(window)
{
    this->set_frame_limit(frame_limit);
    auto cursor_size = sf::Vector2f(radius_pxl,radius_pxl);
    this->set_size(cursor_size);
    auto velocity_0 = sf::Vector2f(0.0f,0.0f);
    this->set_velocity(velocity_0);
    this->init_sprite("./resources/Ghost2.png", 1/7.0);
    this->cursor_attached = true;
}

/// @brief Update cursors state, calc new position for cursor
/// @param window pointer to game render window
void Cursor::update()
{
    Actor::update();

    if (this->cursor_attached)
    {
        sf::Vector2i position = sf::Mouse::getPosition(*window);
        if (position.x < this->get_size().x/2) position.x = this->get_size().x/2;
        if (position.y < this->get_size().x/2) position.y = this->get_size().x/2;
        if (position.x > window->getSize().x - this->get_size().x/2) position.x = window->getSize().x - this->get_size().x/2;
        if (position.y > window->getSize().y - this->get_size().x/2) position.y = window->getSize().y - this->get_size().x/2;
        this->set_position(position);
    }
}

/// @brief Draw cursors in game window
/// @param window pointer to game render window
void Cursor::render()
{
    Actor::render();

    if (this->cursor_attached)
    {
        sf::Vector2i position = sf::Mouse::getPosition(*window);
        bool mouse_cursor_visible = \
        ( (position.x < 0) ||
            (position.y < 0) ||
            (position.x > window->getSize().x) ||
            (position.y > window->getSize().y) );
        window->setMouseCursorVisible(mouse_cursor_visible);
    }
}

void Cursor::cursor_attache()
{
    this->cursor_attached = true;
}

void Cursor::cursor_detache()
{
    this->cursor_attached = false;
    this->window->setMouseCursorVisible(true);
}

