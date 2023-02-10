#include "SplashScreen.hpp"
#include <iostream>

/// @brief Class constructor
SplashScreen::SplashScreen(sf::RenderWindow * window): GameScene(window, 0){
    this->set_bg_color(sf::Color(sf::Color::Black));
    this->set_bg_image("./resources/splash-screen.png");
    //
    //this->set_music(...)
};

/// @brief Class descructor
SplashScreen::~SplashScreen() {

};


/// @brief Check is game running
/// @return true if game in progress, false if should close game window.
const bool SplashScreen::running() const
{
    return this->window->isOpen();
}

/// @brief Update game state on each frame, calculate all game objects internal states.
void SplashScreen::update()
{
    GameScene::update();

    std::cout << sf::Mouse::getPosition(*this->window).x << "x" << sf::Mouse::getPosition(*this->window).y << "\n";
    std::cout << std::flush;
}

/// @brief Draw all game objects in window
void SplashScreen::render()
{
    GameScene::render();
    //this->window->clear(sf::Color(this->bg_color));
    this->window->display();
}

/// @brief 
/// @param ev 
void SplashScreen::poleEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::KeyPressed:  // клавиатура и мышь, нажатие кнопки
            case sf::Event::MouseButtonPressed:  // клавиатура и мышь, нажатие кнопки
                {
                    switch (this->ev.key.code)
                    {
                        case (sf::Keyboard::Escape):
                        case (sf::Keyboard::Space):
                        case (sf::Keyboard::BackSpace):
                        case (sf::Mouse::Left):
                        case (sf::Mouse::Right):
                        case (sf::Mouse::Middle):
                        {
                            this->scene_status = SceneStatus::ENDING;
                        } break;
                    }
                }
                break;
            default:
                break;
        }
    }
}
