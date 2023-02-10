/**
 * \class SplashScreen
 * Implements splashscreen for game. With music and title page. 
 * 
*/

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <list>
#include <utility>
#include "GameScene.hpp"

class SplashScreen: public GameScene
{
public:
    SplashScreen(sf::RenderWindow * window);

    virtual ~SplashScreen();
    const bool running() const;
    
    void poleEvents();

    void update();
    void render();

private:

 
//    void init_variables();
//    void init_window();

//    void create_actors();
    //TODO delete this
    //bool get_cursor_owerlap_enemies(std::vector<Actor *> & overlaped_enemies);
    //bool get_cursor_owerlap_enemies(std::vector< std::vector<Actor *>::iterator > & overlaped_enemies);
    //void owerlap_enemies_actions();
};

