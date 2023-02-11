#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Timer
{
public:
    Timer(sf::RenderWindow * window);
    ~Timer();
    void start();
    void stop();
    sf::Time get_value();
    void render();
private:
    // current value
    sf::Clock * clock;
    bool running;
    sf::Time current_timer_value;
    void update_value();
    sf::RenderWindow * window;
    sf::Font font;
    sf::Text text;
};