#ifndef LSHAPE_INCLUDED
#define LSHAPE_INCLUDED
#include "ShapeInfo.hpp"
#include <array>

struct LShapeInfo : public ShapeInfo
{
    static myShapeArray createShape( );
    static std::vector<uint16_t> startingLocation( );
    static void setColors( std::vector<sf::RectangleShape>&,
                           const std::array<sf::Texture, 7>& );

    static std::vector<uint16_t>
    rotate( const std::vector<uint16_t>& currentLocation );

    static std::vector<sf::Vector2f>
    rotate( const std::vector<sf::RectangleShape>& currentLocation );

    static void rotationSuccess( );
};

#endif
