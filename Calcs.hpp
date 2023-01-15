#include <SFML/Graphics.hpp>
#include <math.h>

sf::Vector2f xy_to_ra(sf::Vector2f XY);
sf::Vector2f ra_to_xy(sf::Vector2f RA);
sf::Vector2f get_centered_after_rotate(sf::Vector2f position, float angle_rad, sf::Vector2f size);
float vector_length(const sf::Vector2f & vect);