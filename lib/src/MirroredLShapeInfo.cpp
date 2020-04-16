#include "../inc/MirroredLShapeInfo.hpp"

MirroredLShapeInfo::myShapeArray MirroredLShapeInfo::createShape( )
{
    return createShapeInternal(
        {240.f, -120.f, 200.f, -120.f, 200.f, -80.f, 200.f, -40.f} );
}
void MirroredLShapeInfo::setColors( std::vector<sf::RectangleShape>& recs,
                                    const std::array<sf::Texture, 7>& textures )
{
    for ( auto& rec : recs )
    {
        rec.setTexture( &textures[3] );
    }
}

std::vector<sf::Vector2f>
MirroredLShapeInfo::rotate( const std::vector<sf::RectangleShape>& tetrisShape )
{
    const auto& currentPos0 = tetrisShape[0].getPosition( );
    const auto& currentPos1 = tetrisShape[1].getPosition( );
    const auto& currentPos2 = tetrisShape[2].getPosition( );
    const auto& currentPos3 = tetrisShape[3].getPosition( );

    switch ( currentRotatedState )
    {
        case 0:
            return {
                moveRectangleLocation( currentPos0, Dir::NegX, Dir::None ),
                moveRectangleLocation( currentPos1, Dir::None, Dir::PosY ),
                moveRectangleLocation( currentPos2, Dir::PosX, Dir::None ),
                moveRectangleLocation( currentPos3, Dir::PosXX, Dir::NegY )};
        case 1:
            return {moveRectangleLocation( currentPos0, Dir::None, Dir::PosYY ),
                    moveRectangleLocation( currentPos1, Dir::PosX, Dir::PosY ),
                    currentPos2,
                    moveRectangleLocation( currentPos3, Dir::NegX, Dir::NegY )};
        case 2:
            return {moveRectangleLocation( currentPos0, Dir::PosXX, Dir::NegY ),
                    moveRectangleLocation( currentPos1, Dir::PosX, Dir::NegYY ),
                    moveRectangleLocation( currentPos2, Dir::None, Dir::NegY ),
                    moveRectangleLocation( currentPos3, Dir::NegX, Dir::None )};
        case 3:
            return {
                moveRectangleLocation( currentPos0, Dir::NegX, Dir::NegY ),
                moveRectangleLocation( currentPos1, Dir::NegXX, Dir::None ),
                moveRectangleLocation( currentPos2, Dir::NegX, Dir::PosY ),
                moveRectangleLocation( currentPos3, Dir::None, Dir::PosYY )};
        default:
            std::runtime_error(
                "error in rotate function, shouldnot have happened" );
    }
    return std::vector<sf::Vector2f>( );
}
void MirroredLShapeInfo::rotationSuccess( )
{
    currentRotatedState = ( currentRotatedState + 1 ) % 4;
};
