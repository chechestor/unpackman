#pragma once
//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


/**
 * \class GameScene
 * Abstract Scene (Splash, Gameplay, Titles)
*/

class GameScene
{
public:
    typedef enum{
        START = 0,
        RUNNING,
        ENDING,
        END,
        HALT,
        SCENE_MAX_STATUS
    } SceneStatus;

    GameScene(sf::RenderWindow * window, unsigned int frame_limit);
    SceneStatus get_status();  ///< is scene running, or end

    virtual void update();
    virtual void render();

    void set_bg_color(sf::Color);
    void set_bg_image(std::string bg_filename);
    void set_music(std::string music_filename);
    
    virtual void poleEvents() = 0;
    
protected:
    sf::RenderWindow * window;  ///< pointer to main game render window
    unsigned int frame_limit;  ///< main game frame limit
    sf::Event ev;  ///< Kbd events object
    SceneStatus scene_status;  ///< current scene status

private:
    // bg image
    sf::Color bg_color;  ///< background game color //TODO
    
    bool bg_image_present;  ///< flag, if bg image set or not
    sf::Texture bg_texture;  ///< texture for background image
    sf::Sprite bg_sprite;  ///< sprite for background image draw

    // bg music
    bool bg_music_present;
    sf::Music bg_music;

    void set_frame_limit(unsigned int frame_limit);

    void start_scene();
    void end_scene();

};
