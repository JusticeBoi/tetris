#ifndef SSHAPE_INCLUDED
#define SSHAPE_INCLUDED
#include "ShapeInfo.hpp"
#include <array>

struct SShapeInfo : public ShapeInfo
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
