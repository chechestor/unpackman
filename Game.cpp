#include "Game.hpp"
#include <iostream>
#include <math.h>

/// @brief Class constructor
Game::Game() {
    this->init_variables();
    this->init_window();
    this->splash_screen = new SplashScreen(this->window);
    this->splash_screen->set_bg_image("./resources/splash-screen.png");
    this->splash_screen->set_music("./resources/pac-man-intro.ogg");

    this->game_play_scene = new GamePlay(this->window, this->frame_limit);
    this->game_play_scene->set_music("./resources/pac-man-intermission.ogg");

    this->game_stage = GameStage::SPLASHSCREEN;
   
};

/// @brief Class descructor
Game:: ~Game() {
    delete this->game_play_scene;
    delete this->splash_screen;
    delete this->window;
};

/// @brief Init game start variables and global game settings
void Game::init_variables()
{
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

/// @brief Initialize game window
void Game::init_window()
{
    this->window = new sf::RenderWindow(
                this->video_mode,
                this->window_title,
                sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(this->frame_limit);
}

void Game::update()
{
    switch (this->game_stage)
    {
        case (GameStage::SPLASHSCREEN):
        {
            this->splash_screen->update();
            this->splash_screen->render();

            auto scene_status = this->splash_screen->get_status();
            if(scene_status == GameScene::SceneStatus::END)
            {
                this->game_stage = GameStage::GAMEPLAY;
            }
        }
        break;
        case (GameStage::GAMEPLAY):
        {
            this->game_play_scene->update();
            this->game_play_scene->render();
            auto scene_status = this->game_play_scene->get_status();
            if(scene_status == GameScene::SceneStatus::END)
            {
                this->window->close();
            }
        }
        break;
    };

}