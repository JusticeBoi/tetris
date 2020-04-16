#include "../inc/SShapeInfo.hpp"

SShapeInfo::myShapeArray SShapeInfo::createShape( )
{
    return createShapeInternal(
        {200.f, -120.f, 200.f, -80.f, 240.f, -80.f, 240.f, -40.f} );
}
void SShapeInfo::setColors( std::vector<sf::RectangleShape>& recs,
                            const std::array<sf::Texture, 7>& textures )
{
    for ( auto& rec : recs )
    {
        rec.setTexture( &textures[4] );
    }
}

std::vector<sf::Vector2f>
SShapeInfo::rotate( const std::vector<sf::RectangleShape>& tetrisShape )
{
    const auto& currentPos0 = tetrisShape[0].getPosition( );
    const auto& currentPos1 = tetrisShape[1].getPosition( );
    const auto& currentPos2 = tetrisShape[2].getPosition( );
    const auto& currentPos3 = tetrisShape[3].getPosition( );

    switch ( currentRotatedState )
    {
        case 0:
            return {
                moveRectangleLocation( currentPos0, Dir::PosX, Dir::PosY ),
                currentPos1,
                moveRectangleLocation( currentPos2, Dir::NegX, Dir::PosY ),
                moveRectangleLocation( currentPos3, Dir::NegXX, Dir::None )};
        case 1:
            return {
                moveRectangleLocation( currentPos0, Dir::NegX, Dir::NegY ),
                currentPos1,
                moveRectangleLocation( currentPos2, Dir::PosX, Dir::NegY ),
                moveRectangleLocation( currentPos3, Dir::PosXX, Dir::None )};
        default:
            std::runtime_error(
                "error in rotate function, shouldnot have happened" );
    }
    return std::vector<sf::Vector2f>( );
}
void SShapeInfo::rotationSuccess( )
{
    currentRotatedState = ( currentRotatedState + 1 ) % 2;
};
