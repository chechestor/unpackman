#include "Calcs.hpp"

/// @brief Presecnts gived vector in radial form 
/// @param XY vector in XY linear coordinates
/// @return vector in radial coordinates (radius in pixels, angle in rad)
sf::Vector2f xy_to_ra(sf::Vector2f XY)
{
    float x = XY.x;
    float y = XY.y;
    float r = sqrt(x*x + y*y);
    float a = atan(y/x);
    if (a != a) a = 0;
    if (x < 0) a += M_PI;
    return sf::Vector2f(r,a);
}

/// @brief Presecnts gived radial vector in XY coordinates 
/// @param RA vector in radial coordinates
/// @return vector in XY linear coordinates (X in pixels, Y in pixels)
sf::Vector2f ra_to_xy(sf::Vector2f RA)
{
    float r = RA.x;
    float a = RA.y;
    float y = r * sin(a);
    float x = r * cos(a);
    return sf::Vector2f(x,y);
}

/// @brief Calculate new rect position for rotate rectangle by center.
/// Helper function calculates sprite moving reqired for rotate sprite around the center of sprite.
/// In SFML sprite rotation is around the top left corner of the sprite.
/// @param position required destination position of sprites center
/// @param angle_rad the angle by witch the sprite is rotated
/// @param size sprite size
/// @return Corresponding position for move sprites corner 
sf::Vector2f get_centered_after_rotate(sf::Vector2f position, float angle_rad, sf::Vector2f size)
{
    sf::Vector2f center_begin_xy = size / (float)2.0;
    sf::Vector2f center_begin_ra = xy_to_ra(center_begin_xy);
    sf::Vector2f center_new_ra = center_begin_ra + sf::Vector2f(0, angle_rad);
    sf::Vector2f center_new_xy = ra_to_xy(center_new_ra);
    sf::Vector2f new_xy = position - center_new_xy;
    return new_xy;
}

/// @brief Calc vectors abs length
/// @param vect vector in XY
/// @return vectors abs length (in pixels)
float vector_length(const sf::Vector2f & vect)
{
    return sqrtf( vect.x * vect.x + vect.y * vect.y );
}
