#include "../inc/ZShapeInfo.hpp"

ZShapeInfo::myShapeArray ZShapeInfo::createShape( )
{
    return createShapeInternal(
        {240.f, -120.f, 200.f, -80.f, 240.f, -80.f, 200.f, -40.f} );
}
void ZShapeInfo::setColors( std::vector<sf::RectangleShape>& recs,
                            const std::array<sf::Texture, 7>& textures )
{
    for ( auto& rec : recs )
    {
        rec.setTexture( &textures[6] );
    }
}

std::vector<sf::Vector2f>
ZShapeInfo::rotate( const std::vector<sf::RectangleShape>& tetrisShape )
{
    const auto& currentPos0 = tetrisShape[0].getPosition( );
    const auto& currentPos1 = tetrisShape[1].getPosition( );
    const auto& currentPos2 = tetrisShape[2].getPosition( );
    const auto& currentPos3 = tetrisShape[3].getPosition( );

    switch ( currentRotatedState )
    {
        case 0:
            return {
                moveRectangleLocation( currentPos0, Dir::NegX, Dir::PosY ),
                moveRectangleLocation( currentPos1, Dir::PosX, Dir::PosY ),
                currentPos2,
                moveRectangleLocation( currentPos3, Dir::PosXX, Dir::None )};
        case 1:
            return {
                moveRectangleLocation( currentPos0, Dir::PosX, Dir::NegY ),
                moveRectangleLocation( currentPos1, Dir::NegX, Dir::NegY ),
                currentPos2,
                moveRectangleLocation( currentPos3, Dir::NegXX, Dir::None )};
        default:
            std::runtime_error(
                "error in rotate function, shouldnot have happened" );
    }
    return std::vector<sf::Vector2f>( );
}
void ZShapeInfo::rotationSuccess( )
{
    currentRotatedState = ( currentRotatedState + 1 ) % 2;
};
