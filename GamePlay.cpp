#include <iostream>
#include <math.h>
#include "GamePlay.hpp"
#include "Calcs.hpp"

/// @brief Class constructor
GamePlay::GamePlay(sf::RenderWindow * window, unsigned int frame_limit): GameScene(window, frame_limit){
    this->init_variables();
    this->create_actors();
    this->cursor = new Cursor(this->window, this->frame_limit, this->cursor_size_px);
    this->timer = new Timer(this->window);
};

/// @brief Class descructor
GamePlay::~GamePlay() {
    //delete all actors
    for (auto actor : this->enemy_actors)
    {
        delete actor;
    }
    this->enemy_actors.clear();
    
    delete this->timer;
    delete this->cursor;
    delete this->window;
};

/// @brief Init game start variables and global game settings
void GamePlay::init_variables()
{
    this->set_bg_color(sf::Color(0x30, 0x10, 0x05));  // dark drown
    this->frame_limit = 100;  // frames per s
    this->cursor_size_px = 30;  // px, sprite square 
    this->enemy_size_px = 30;  // px, sprite square
    this->max_enemies_qty = 30;  // Enemies qty on game field
    this->enemy_speed = 130; //px/s

    this->game_failed = false;  // true, when pacmen overlap ghost
}

/// @brief Check is game running
/// @return true if game in progress, false if should close game window.
const bool GamePlay::running() const
{
    return this->window->isOpen();
}

/// @brief Update game state on each frame, calculate all game objects internal states.
void GamePlay::update()
{
    if (this->get_status() == GameScene::SceneStatus::START)
    {
        this->timer->start();
    }
    GameScene::update();

    //this->window->setMouseCursorVisible(false);  //TODO move to START sctions
    
    std::cout << sf::Mouse::getPosition(*this->window).x << "x" << sf::Mouse::getPosition(*this->window).y << "\n";
    std::cout << std::flush;
    this->update_all_enemy_actors();
    this->cursor->update();

    if (!this->game_failed)
    {
        if (this->overlap_check())
        {
            this->game_failed = true;
            this->overlap_enemies_actions();
        }
    }
}

/// @brief Draw all game objects in window
void GamePlay::render()
{
    GameScene::render();
    
    this->render_all_enemy_actors();
    this->cursor->render();
    this->timer->render();
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
        actor->update();
    }
}

/// @brief Draw current state af all enemy actors
void  GamePlay::render_all_enemy_actors()
{
    for (auto actor : this->enemy_actors)
    {
        actor->render();
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

        // random direction ov velocity vector
        float angle = ((rand() % 1024 ) * 2 * M_PI) / 1024;
        auto velocity = sf::Vector2f(this->enemy_speed * sin(angle), enemy_speed * cos(angle));

        auto size = sf::Vector2f(this->enemy_size_px, this->enemy_size_px);

        Enemy * actor = new Enemy(this->window, this->frame_limit, position, size, velocity);

        this->add_enemy_actor(actor);
    }

}

/// @brief pole keyboard events, do actions
void GamePlay::poleEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                this->scene_status = SceneStatus::ENDING;
                this->window->close();  //TODO: сделать выход из сцены со статусом HALT
                break;
            case sf::Event::KeyPressed:  // клавиатура и мышь, нажатие кнопки
                {
                    if (this->ev.key.code == sf::Keyboard::Escape)
                    {
                        this->scene_status = SceneStatus::ENDING;
                    }
                }
                break;
            case sf::Event::KeyReleased:  // клавиатура и мышь, отпускание кнопки
                //
                break;
            default:
                break;
        }
    }
}

bool GamePlay::overlap_check()
{
    for (auto enemy : this->enemy_actors)
    {
        //
        auto distance_vector_xy = this->cursor->get_position() - (enemy->get_position());
        auto distance_vector_ra = xy_to_ra(distance_vector_xy);
        auto min_distance = (this->enemy_size_px + this->cursor_size_px) / 2;
        if (distance_vector_ra.x < min_distance)
        {
            return true;
        }
    }
    return false;
}

void GamePlay::overlap_enemies_actions()
{
    // stop all enemies
    for (auto enemy : this->enemy_actors)
        {
            enemy->set_velocity(enemy->get_velocity().x / 10000, enemy->get_velocity().y / 10000 );
            //enemy->set_velocity(0, 0);
        }

    // detach cursor from sprite
    this->cursor->cursor_detache();

    // stop counter
    this->set_bg_color(sf::Color::Blue);

    this->timer->stop();
}
