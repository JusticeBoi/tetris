#ifndef SHAPE_INFO_INCLUDED
#define SHAPE_INFO_INCLUDED

#include <array>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


struct ShapeInfo
{
    using myShapeArray = std::vector<sf::RectangleShape>;
    static myShapeArray
    createShapeInternal( const std::array<float, 8>& positions );
    inline static uint8_t currentRotatedState = 0;
};
#include "RotationHelpers.hpp"

#endif
