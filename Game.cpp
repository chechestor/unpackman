#include "Game.hpp"
#include <iostream>
#include <math.h>

/// @brief Class constructor
Game::Game() {
    this->init_variables();
    this->init_window();
    this->create_actors();
    this->cursor = new Cursor(this->frame_limit, this->cursor_size_px);
};

/// @brief Class descructor
Game:: ~Game() {

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
void Game::init_variables()
{
    //this->window = nullptr;
    this->video_mode.width = 640;
    this->video_mode.height = 480;
    this->window_title = "3x4games";
    this->bg_color = sf::Color(0x30, 0x10, 0x05);  // dark drown
    this->frame_limit = 100;  // frames per s
    this->cursor_size_px = 30;  // px, sprite square 
    this->enemy_size_px = 30;  // px, sprite square
    this->max_enemies_qty = 30;  // Enemies qty on game field
    this->enemy_speed = 130; //px/s
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

/// @brief Update game state on each frame, calculate all game objects internal states.
void Game::update()
{
    this->poleEvents();
    std::cout << sf::Mouse::getPosition(*this->window).x << "x" << sf::Mouse::getPosition(*this->window).y << "\n";
    std::cout << std::flush;
    this->update_all_enemy_actors();
    this->cursor->update(this->window);
    //this->owerlap_enemies_actions();  // actions on owerlap enemies under cursor
}

/// @brief Draw all game objects in window
void Game::render()
{
    this->window->clear(sf::Color(this->bg_color));
    this->render_all_enemy_actors();
    this->cursor->render(this->window);
    this->window->display();
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

/// @brief Add a new one enemy (mad packman) in the game enemy collection
/// @param actor actor ptr to add to enemy collection
void Game::add_enemy_actor(Actor * actor)
{
    this->enemy_actors.push_front(actor);
}

/// @brief delete the enemy (mad packman) from the game enemy collection
/// @param i_act An iterator pointing to the actor object to be removed from anemy collection
void Game::remove_actor(std::list<Actor*>::iterator i_act)
{
    this->enemy_actors.erase(i_act);
}

/// @brief delete the enemy (mad packman) from the game enemy collection
/// @param actor Pointer to the actor object to be removed from anemy collection
void Game::remove_actor(Actor * actor)
{
    this->enemy_actors.remove(actor);
}

/// @brief Calc new state of all enemies
void  Game::update_all_enemy_actors()
{
    for (auto actor : this->enemy_actors)
    {
        actor->update(this->window);
    }
}

/// @brief Draw current state af all enemy actors
void  Game::render_all_enemy_actors()
{
    for (auto actor : this->enemy_actors)
    {
        actor->render(this->window);
    }
}

/// @brief Create all enemies on the start of the game
void  Game::create_actors()
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

    /*
    TODO: float fluctuations visualisation
    int max_enemies_x = 100;
    int max_enemies_y = 100;
    for (int x = 0; x < max_enemies_x; x++)
    for (int y = 0; y < max_enemies_y; y++)
    {
        auto size = sf::Vector2f(5, 5);
        auto position = sf::Vector2f(x,y);
        auto velocity = sf::Vector2f(max_speed, (float)max_speed);
        
        Enemy * actor = new Enemy(this->frame_limit, position, size, velocity);

        this->add_enemy_actor(actor);
    }
    */
}

//TODO: remove it
/*
bool Game::get_cursor_owerlap_enemies(std::vector< std::vector<Actor *>::iterator > & overlaped_enemies)
{
    overlaped_enemies.clear();
    for (auto penemy = this->enemy_actors.begin(); penemy != this->enemy_actors.end() ; ++penemy)
    {
        auto center_distance_vector = this->cursor->get_position() - (*penemy)->get_position();
        auto center_distance = this->vector_length(center_distance_vector);

        if (center_distance < ( (*penemy)->get_size().x/2 + this->cursor->get_size().x/2))
        {
            overlaped_enemies.push_back(penemy);
        }
    }
    if (overlaped_enemies.size() > 0)
    {
        return true;
    }
    return false;
}

void Game::owerlap_enemies_actions()
{
    this->get_cursor_owerlap_enemies(this->owerlaped_enemies_list);
    for (auto penemy : this->owerlaped_enemies_list)
    {
        delete *penemy;
        this->enemy_actors.erase(penemy);
    }
}
*/
