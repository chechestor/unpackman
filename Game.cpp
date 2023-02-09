#include "Game.hpp"
#include <iostream>
#include <math.h>

/// @brief Class constructor
Game::Game() {
    this->init_variables();
    this->init_window();
    this->game_play_scene = new GamePlay(this->window, this->frame_limit);
};

/// @brief Class descructor
Game:: ~Game() {
    delete this->game_play_scene;
    delete this->window;
};

/// @brief Init game start variables and global game settings
void Game::init_variables()
{
    //this->window = nullptr;
    this->video_mode.width = 640;
    this->video_mode.height = 480;
    this->window_title = "3x4games";
    this->bg_color = sf::Color(0x30, 0x10, 0x05);  // dark drown
    this->frame_limit = 100;  // frames per s
}

/// @brief Check is game running
/// @return true if game in progress, false if should close game window.
const bool Game::running() const
{
    return this->window->isOpen();
}

/// @brief pole keyboard events, do actions
void Game::poleEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:  // клавиатура и мышь, нажатие кнопки
            //
            break;
        case sf::Event::KeyReleased:  // клавиатура и мышь, отпускание кнопки
            //
            break;
        
        default:
            break;
        }
    }
}

/// @brief Initialize game window
void Game::init_window()
{
    this->window = new sf::RenderWindow(
                this->video_mode,
                this->window_title,
                sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(this->frame_limit);
    this->window->setMouseCursorVisible(false);
}

void Game::update()
{
    this->poleEvents();
    this->game_play_scene->update();
    this->game_play_scene->render();
}