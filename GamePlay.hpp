/**
 * \class GamePlay
 * Implements gameflow, create and init game ojects, interact between objects, count scores.
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
#include "Actor.hpp"
#include <utility>
#include "Enemy.hpp"
#include "Cursor.hpp"
#include "GameScene.hpp"

class GamePlay: public GameScene
{
public:
    GamePlay(sf::RenderWindow * window, unsigned int frame_limit);
    virtual ~GamePlay();
    const bool running() const;
    void poleEvents();
    void update();
    void render();

private:
    // Game scene settings
    unsigned int cursor_size_px;  ///< Cursor size X*Y
    unsigned int enemy_size_px;  ///< Enemy size X*Y
    int max_enemies_qty;  ///< Enemy quantity in game
    float enemy_speed;  ///< Enemies moving speed, pixels/s

    // Variables
    std::list<Actor *> enemy_actors;  ///< List of all mad pacmans actors in game
    std::vector< std::vector<Actor *>::iterator > owerlaped_enemies_list;  ///< Enemies who owerlapped cursor
    Cursor * cursor;  ///< Actor who represents cursor

    void init_variables();
    void update_all_enemy_actors();
    void add_enemy_actor(Actor * actor);
    void render_all_enemy_actors();
    void remove_actor(std::list<Actor*>::iterator i_act);
    void remove_actor(Actor * actor);
    void create_actors();
    //TODO delete this
    //bool get_cursor_owerlap_enemies(std::vector<Actor *> & overlaped_enemies);
    //bool get_cursor_owerlap_enemies(std::vector< std::vector<Actor *>::iterator > & overlaped_enemies);
    //void owerlap_enemies_actions();
};

