#include "Timer.hpp"
#include <string>

Timer::Timer(sf::RenderWindow * window)
{
    this->window = window;
    this->clock = new sf::Clock();
    update_value();
    this->running = false;

    this->font.loadFromFile("./resources/arial.ttf");
    this->text.setFont(font);
    this->text.setCharacterSize(24); // in pixels, not points!
    this->text.setFillColor(sf::Color::White);
    this->text.setStyle(sf::Text::Bold);
    this->text.setPosition(0, 0);
}

Timer::~Timer()
{
    delete this->clock;
}

void Timer::start()
{
    this->clock->restart();
    this->running = true;
}

void Timer::stop()
{
    this->running = false;
}

sf::Time Timer::get_value()
{
    return this->current_timer_value;
}

void Timer::render()
{
    this->update_value();
    char time_string[] = "XX:XX.XXXn\0";
    unsigned int mse = this->current_timer_value.asMilliseconds() % 1000;
    unsigned int ss = (unsigned int)this->current_timer_value.asSeconds() % 60;
    unsigned int mi = ((unsigned int)this->current_timer_value.asSeconds() / 60) % 60;
    sprintf(time_string, "%02d:%02d.%03d", mi, ss, mse);
    

    this->text.setString(time_string);

    this->window->draw(this->text);
}

void Timer::update_value()
{
    if (this->running)
    {
        this->current_timer_value = this->clock->getElapsedTime();
    }
}