#include "GameScene.hpp"

GameScene::GameScene(sf::RenderWindow * window, unsigned int frame_limit)
{
    this->window = window;
    this->set_frame_limit(frame_limit);
    this->state = SceneStatus::INIT;
}

GameScene::SceneStatus GameScene::status()  ///< is scene running, or end
{
    return this->SceneStatus::RUNNING;
}

void GameScene::update()
{
    // check keyboard actions
    poleEvents();

    // update status
    // todo

    // update scene
    // ...
}

void GameScene::render()
{

}
//---------------------------------------------------------------
//private methods
//---------------------------------------------------------------
void GameScene::set_frame_limit(unsigned int frame_limit)
{
    this->frame_limit = frame_limit;
}

/// @brief pole keyboard events, do actions
void GameScene::poleEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        //case sf::Event::Closed:
        //    this->window->close();
        //    break;
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
