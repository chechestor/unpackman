#pragma once
//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/**
 * \class GameScene
 * Abstract Scene (Splash, Gameplay, Titles)
*/

class GameScene
{
public:
    typedef enum{
        INIT = 0,
        RUNNING,
        END,
        HALT,
        SCENE_MAX_STATUS
    } SceneStatus;

    GameScene(sf::RenderWindow * window, unsigned int frame_limit);
    //virtual ~GameScene();
    SceneStatus status();  ///< is scene running, or end

    virtual void update();
    virtual void render();

protected:
    sf::RenderWindow * window;  ///< pointer to main game render window
    unsigned int frame_limit;  ///< main game frame limit
    sf::Color bg_color;  ///< background game color //TODO
    sf::Event ev;  ///< Kbd events object

private:

    SceneStatus state;  ///< current scene status

    void set_frame_limit(unsigned int frame_limit);
    void poleEvents();
};
