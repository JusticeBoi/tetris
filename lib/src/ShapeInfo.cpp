#include "../inc/ShapeInfo.hpp"
#include <random>

ShapeInfo::myShapeArray
ShapeInfo::createShapeInternal( const std::array<float, 8>& positions )
{

    myShapeArray arr = {sf::RectangleShape( sf::Vector2f( 40.f, 40.f ) ),
                        sf::RectangleShape( sf::Vector2f( 40.f, 40.f ) ),
                        sf::RectangleShape( sf::Vector2f( 40.f, 40.f ) ),
                        sf::RectangleShape( sf::Vector2f( 40.f, 40.f ) )};

    arr[0].setPosition( positions[0], positions[1] );
    arr[1].setPosition( positions[2], positions[3] );
    arr[2].setPosition( positions[4], positions[5] );
    arr[3].setPosition( positions[6], positions[7] );
    return arr;
}
