#include "../inc/TShapeInfo.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <stdexcept>

TShapeInfo::myShapeArray TShapeInfo::createShape( )
{
    return createShapeInternal(
        {200.f, -80.f, 160.f, -40.f, 200.f, -40.f, 240.f, -40.f} );
}
void TShapeInfo::setColors( std::vector<sf::RectangleShape>& recs,
                            const std::array<sf::Texture, 7>& textures )
{
    for ( auto& rec : recs )
    {
        rec.setTexture( &textures[5] );
    }
}

std::vector<sf::Vector2f>
TShapeInfo::rotate( const std::vector<sf::RectangleShape>& tetrisShape )
{
    const auto& currentPos0 = tetrisShape[0].getPosition( );
    const auto& currentPos1 = tetrisShape[1].getPosition( );
    const auto& currentPos2 = tetrisShape[2].getPosition( );
    const auto& currentPos3 = tetrisShape[3].getPosition( );

    switch ( currentRotatedState )
    {
        case 0:
            return {moveRectangleLocation( currentPos0, Dir::NegX, Dir::PosY ),
                    moveRectangleLocation( currentPos1, Dir::PosX, Dir::PosY ),
                    currentPos2,
                    moveRectangleLocation( currentPos3, Dir::NegX, Dir::NegY )};
        case 1:
            return {moveRectangleLocation( currentPos0, Dir::PosX, Dir::PosY ),
                    moveRectangleLocation( currentPos1, Dir::PosX, Dir::NegY ),
                    currentPos2,
                    moveRectangleLocation( currentPos3, Dir::NegX, Dir::PosY )};
        case 2:
            return {moveRectangleLocation( currentPos0, Dir::PosX, Dir::NegY ),
                    moveRectangleLocation( currentPos1, Dir::NegX, Dir::NegY ),
                    currentPos2,
                    moveRectangleLocation( currentPos3, Dir::PosX, Dir::PosY )};
        case 3:
            return {moveRectangleLocation( currentPos0, Dir::NegX, Dir::NegY ),
                    moveRectangleLocation( currentPos1, Dir::NegX, Dir::PosY ),
                    currentPos2,
                    moveRectangleLocation( currentPos3, Dir::PosX, Dir::NegY )};
        default:
            std::runtime_error(
                "error in rotate function, shouldnot have happened" );
    }
    return std::vector<sf::Vector2f>( );
}
void TShapeInfo::rotationSuccess( )
{
    currentRotatedState = ( currentRotatedState + 1 ) % 4;
};
