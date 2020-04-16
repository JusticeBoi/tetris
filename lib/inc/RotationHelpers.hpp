#ifndef ROTATION_HELPERS_INCLUDED
#define ROTATION_HELPERS_INCLUDED
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <utility>

enum Dir : int8_t
{
    PosX = 1,
    PosXX = 2,
    PosY = 1,
    PosYY = 2,
    NegX = -1,
    NegXX = -2,
    NegY = -1,
    NegYY = -2,
    None = 0
};

inline sf::Vector2f
moveRectangleLocation( const sf::Vector2f& vec, Dir X, Dir Y )
{

    return sf::Vector2f{vec.x + ( 40.f * X ), vec.y + ( 40.f * Y )};
}

#endif
