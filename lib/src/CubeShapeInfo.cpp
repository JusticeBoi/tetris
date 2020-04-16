#include "../inc/CubeShapeInfo.hpp"
#include <SFML/System/Vector2.hpp>

CubeShapeInfo::myShapeArray CubeShapeInfo::createShape( )
{
    return createShapeInternal(
        {200.f, -80.f, 240.f, -80.f, 200.f, -40.f, 240.f, -40.f} );
}

void CubeShapeInfo::setColors( std::vector<sf::RectangleShape>& recs,
                               const std::array<sf::Texture, 7>& textures )
{
    for ( auto& rec : recs )
    {
        rec.setTexture( &textures[0] );
    }
}
std::vector<sf::Vector2f>
CubeShapeInfo::rotate( const std::vector<sf::RectangleShape>& tetrisShape )
{
    return {tetrisShape[0].getPosition( ), tetrisShape[1].getPosition( ),
            tetrisShape[2].getPosition( ), tetrisShape[3].getPosition( )};
}

void CubeShapeInfo::rotationSuccess( ){};
