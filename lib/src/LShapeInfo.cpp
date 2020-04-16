#include "../inc/LShapeInfo.hpp"
#include <limits>

LShapeInfo::myShapeArray LShapeInfo::createShape( )
{
    return createShapeInternal(
        {200.f, -120.f, 240.f, -120.f, 240.f, -80.f, 240.f, -40.f} );
}
void LShapeInfo::setColors( std::vector<sf::RectangleShape>& recs,
                            const std::array<sf::Texture, 7>& textures )
{
    for ( auto& rec : recs )
    {
        rec.setTexture( &textures[2] );
    }
}

std::vector<sf::Vector2f>
LShapeInfo::rotate( const std::vector<sf::RectangleShape>& tetrisShape )
{
    const auto& currentPos0 = tetrisShape[0].getPosition( );
    const auto& currentPos1 = tetrisShape[1].getPosition( );
    const auto& currentPos2 = tetrisShape[2].getPosition( );
    const auto& currentPos3 = tetrisShape[3].getPosition( );

    switch ( currentRotatedState )
    {
        case 0:
            return {
                moveRectangleLocation( currentPos0, Dir::None, Dir::PosY ),
                moveRectangleLocation( currentPos1, Dir::NegX, Dir::None ),
                moveRectangleLocation( currentPos2, Dir::None, Dir::NegY ),
                moveRectangleLocation( currentPos3, Dir::PosX, Dir::NegYY )};
        case 1:
            return {
                moveRectangleLocation( currentPos0, Dir::PosX, Dir::PosY ),
                moveRectangleLocation( currentPos1, Dir::None, Dir::PosYY ),
                moveRectangleLocation( currentPos2, Dir::NegX, Dir::PosY ),
                moveRectangleLocation( currentPos3, Dir::NegXX, Dir::None )};
        case 2:
            return {moveRectangleLocation( currentPos0, Dir::PosX, Dir::NegYY ),
                    moveRectangleLocation( currentPos1, Dir::PosXX, Dir::NegY ),
                    moveRectangleLocation( currentPos2, Dir::PosX, Dir::None ),
                    moveRectangleLocation( currentPos3, Dir::None, Dir::PosY )};
        case 3:
            return {moveRectangleLocation( currentPos0, Dir::NegXX, Dir::None ),
                    moveRectangleLocation( currentPos1, Dir::NegX, Dir::NegY ),
                    moveRectangleLocation( currentPos2, Dir::None, Dir::None ),
                    moveRectangleLocation( currentPos3, Dir::PosX, Dir::PosY )};
        default:
            std::runtime_error(
                "error in rotate function, shouldnot have happened" );
    }
    return std::vector<sf::Vector2f>( );
}
void LShapeInfo::rotationSuccess( )
{
    currentRotatedState = ( currentRotatedState + 1 ) % 4;
};
