/**
 * \class Game
 * Implements gameflow, create and init game ojects, interact between objects, count scores.
 * 
*/

#pragma once
#include <string>
#include "SplashScreen.hpp"
#include "GamePlay.hpp"

class Game
{
public:
    Game();
    virtual ~Game();
    const bool running() const;
    void update();

private:
    // Game settings
    sf::VideoMode video_mode;  ///< Window resolution 
    std::string window_title;  ///< Game window tittle
    sf::Color bg_color;  ///< background game color
    unsigned int frame_limit;  ///< Game framerate

    // Variables
    sf::RenderWindow * window;  ///< Main render game window
    sf::Event ev;  ///< Kbd events object
    
    SplashScreen * splash_screen;
    GamePlay * game_play_scene;

    typedef enum {
        SPLASHSCREEN = 0,
        GAMEPLAY
    } GameStage;
    GameStage game_stage;

    void init_variables();
    void init_window();
};

