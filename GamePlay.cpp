#include "GamePlay.hpp"
#include <iostream>
#include <math.h>

/// @brief Class constructor
GamePlay::GamePlay(sf::RenderWindow * window, unsigned int frame_limit): GameScene(window, frame_limit){
    this->init_variables();
    this->create_actors();
    this->cursor = new Cursor(this->frame_limit, this->cursor_size_px);
};

/// @brief Class descructor
GamePlay::~GamePlay() {

    delete this->window;
    delete this->cursor;
    //delete all actors
    for (auto actor : this->enemy_actors)
    {
        delete actor;
    }
    this->enemy_actors.clear();
};

/// @brief Init game start variables and global game settings
void GamePlay::init_variables()
{
    this->bg_color = sf::Color(0x30, 0x10, 0x05);  // dark drown
    this->frame_limit = 100;  // frames per s
    this->cursor_size_px = 30;  // px, sprite square 
    this->enemy_size_px = 30;  // px, sprite square
    this->max_enemies_qty = 30;  // Enemies qty on game field
    this->enemy_speed = 130; //px/s
}

/// @brief Check is game running
/// @return true if game in progress, false if should close game window.
const bool GamePlay::running() const
{
    return this->window->isOpen();
}

/// @brief pole keyboard events, do actions
/*void GamePlay::poleEvents()
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
*/

/// @brief Update game state on each frame, calculate all game objects internal states.
void GamePlay::update()
{
    GameScene::update();

    std::cout << sf::Mouse::getPosition(*this->window).x << "x" << sf::Mouse::getPosition(*this->window).y << "\n";
    std::cout << std::flush;
    this->update_all_enemy_actors();
    this->cursor->update(this->window);
}

/// @brief Draw all game objects in window
void GamePlay::render()
{
    GameScene::render();
    
    this->window->clear(sf::Color(this->bg_color));
    this->render_all_enemy_actors();
    this->cursor->render(this->window);
    this->window->display();
}

/// @brief Add a new one enemy (mad packman) in the game enemy collection
/// @param actor actor ptr to add to enemy collection
void GamePlay::add_enemy_actor(Actor * actor)
{
    this->enemy_actors.push_front(actor);
}

/// @brief delete the enemy (mad packman) from the game enemy collection
/// @param i_act An iterator pointing to the actor object to be removed from anemy collection
void GamePlay::remove_actor(std::list<Actor*>::iterator i_act)
{
    this->enemy_actors.erase(i_act);
}

/// @brief delete the enemy (mad packman) from the game enemy collection
/// @param actor Pointer to the actor object to be removed from anemy collection
void GamePlay::remove_actor(Actor * actor)
{
    this->enemy_actors.remove(actor);
}

/// @brief Calc new state of all enemies
void  GamePlay::update_all_enemy_actors()
{
    for (auto actor : this->enemy_actors)
    {
        actor->update(this->window);
    }
}

/// @brief Draw current state af all enemy actors
void  GamePlay::render_all_enemy_actors()
{
    for (auto actor : this->enemy_actors)
    {
        actor->render(this->window);
    }
}

/// @brief Create all enemies on the start of the game
void  GamePlay::create_actors()
{

    //create 10 Enemies
    for (int i = 0; i < this->max_enemies_qty; i++)
    {
        // rendom position in perimeter
        auto position = sf::Vector2f(0,0);
        int H = this->window->getSize().y;
        int W = this->window->getSize().x;
        auto perimeter_position = rand() % (2 * (W + H));
        if (perimeter_position < W)
        {
            position = sf::Vector2f(perimeter_position,0);
        } else if (perimeter_position < (W + H))
        {
            position = sf::Vector2f(0, perimeter_position-W);
        } else if (perimeter_position < (W + H + W))
        {
            position = sf::Vector2f(perimeter_position - W - H, H);
        } else
        {
            position = sf::Vector2f(W, perimeter_position - W - H - W);
        }
        // TODO: model Big Bang: position = sf::Vector2f(float(W/2),float(H/2));

        // random direction ov velocity vector
        float angle = ((rand() % 1024 ) * 2 * M_PI) / 1024;
        auto velocity = sf::Vector2f(this->enemy_speed * sin(angle), enemy_speed * cos(angle));

        auto size = sf::Vector2f(this->enemy_size_px, this->enemy_size_px);

        Enemy * actor = new Enemy(this->frame_limit, position, size, velocity);

        this->add_enemy_actor(actor);
    }

}
