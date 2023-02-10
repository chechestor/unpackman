#include "GameScene.hpp"

GameScene::GameScene(sf::RenderWindow * window, unsigned int frame_limit)
{
    this->window = window;
    this->set_frame_limit(frame_limit);
    this->bg_color = sf::Color::Black;
    this->bg_image_present = false;
    this->bg_music_present = false;
    this->scene_status = SceneStatus::START;
}

GameScene::SceneStatus GameScene::get_status()  ///< is scene running, or end
{
    return this->scene_status;
}

void GameScene::update()
{
    // check keyboard actions
    this->poleEvents();

    // update status
    switch (this->scene_status)
    {
        case (SceneStatus::START):
        {
            this->start_scene();
            this->scene_status = SceneStatus::RUNNING;
        }
        break;
        
        case (SceneStatus::ENDING):
        {
            this->end_scene();
            this->scene_status = SceneStatus::END;
        }
        break;
    }
}

void GameScene::render()
{
    this->window->clear(this->bg_color);
    if (this->bg_image_present)
    {
        this->window->clear(sf::Color::Blue);
        this->window->draw(this->bg_sprite);
    }

    //window->display(); // may call from child class
}

/// @brief 
/// @param  
void GameScene::set_bg_color(sf::Color bg_color)
{
    this->bg_color = bg_color;
}


/// @brief Sets background image for scene.
/// @param bg_filename - path to file with background image for scene.
void GameScene::set_bg_image(std::string bg_filename)
{
    this->bg_texture.loadFromFile(bg_filename);
    this->bg_sprite.setTexture(this->bg_texture);
    this->bg_sprite.setScale((this->window->getSize().x / (float)this->bg_texture.getSize().x), \
                             (this->window->getSize().y / (float)this->bg_texture.getSize().y));
    this->bg_sprite.setPosition(0,0);
    this->bg_image_present = true;
}

void GameScene::set_music(std::string music_filename)
{
    this->bg_music.openFromFile(music_filename);
    this->bg_music.setVolume(10);  //TODO: перенести в конструктор
    this->bg_music_present = true;
}

//---------------------------------------------------------------
//private methods
//---------------------------------------------------------------
void GameScene::set_frame_limit(unsigned int frame_limit)
{
    this->frame_limit = frame_limit;
}

void GameScene::start_scene()
{
    // code for start scene
    this->scene_status = SceneStatus::RUNNING;
    if (this->bg_music_present)
    {
        this->bg_music.play();
    }
}

void GameScene::end_scene()
{
    // code for start scene
    this->scene_status = SceneStatus::END;
    if (this->bg_music_present)
    {
        this->bg_music.stop();
    }
}


