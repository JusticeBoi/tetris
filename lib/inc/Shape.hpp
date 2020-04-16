#ifndef SHAPE_INCLUDED
#define SHAPE_INCLUDED

#include "IShape.hpp"
#include "macros.h"
#include <SFML/System/Vector2.hpp>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>


template<typename ShapeInfo> class Shape final : public IShape
{
  public:
    void move( int8_t right, int8_t bottom ) override;
    void rotate( ) override;

    Shape( std::array<uint8_t, 264>& );
    Shape( ) = delete;
    Shape( const Shape& s ) = delete;
    Shape( Shape&& s ) = delete;
    Shape& operator=( Shape&& s ) = delete;
    Shape& operator=( const Shape& s ) = delete;
};

template<typename ShapeInfo>
Shape<ShapeInfo>::Shape( std::array<uint8_t, 264>& arr )
    : IShape( ShapeInfo::createShape( ), arr )
{
    ShapeInfo::setColors( tetrisShape_, textures );
};

template<typename ShapeInfo>
void Shape<ShapeInfo>::move( int8_t right, int8_t bottom )
{
    using constants::oneOverForty;
    const auto positions = getPositionsOfRectangles( );
    const float toRight = 40.f * right;
    const float toBot = 40.f * bottom;
    for ( const auto& pos : positions )
    {

        const float newX = pos.x + toRight;
        const float newY = pos.y + toBot;
        if ( newX < -0.1f || newX > 440.f )
            return;
        if ( pos.y < -39.f )
            continue;

        uint16_t posIndex = static_cast<uint16_t>(
            ( newX * oneOverForty ) + ( newY * oneOverForty ) * 12 );
        if ( filledGridMap_[posIndex] || newY > 841.f )
        {
            if ( std::abs( newY - pos.y ) > 1.f )
            {
                stopped = 1;
                ShapeInfo::currentRotatedState = 0;
            }
            clock.restart( );
            return;
        }
        else if ( stopped && clock.getElapsedTime( ).asMilliseconds( ) > 250 )
        {
            return;
        }
    }
    for ( auto& rec : tetrisShape_ )
    {
        rec.move( toRight, toBot );
    }
}
template<typename ShapeInfo> void Shape<ShapeInfo>::rotate( )
{
    using constants::oneOverForty;
    if ( stopped )
        return;
    const std::vector<sf::Vector2f> newLocations =
        ShapeInfo::rotate( tetrisShape_ );

    if ( std::any_of( std::cbegin( newLocations ), std::cend( newLocations ),
                      []( const auto& v ) {
                          return ( v.x > 441.f || v.x < 0.f || v.y > 841.f );
                      } ) )
        return;

    std::vector<uint16_t> indices;
    indices.reserve( 4 );
    std::transform(
        std::cbegin( newLocations ), std::cend( newLocations ),
        std::back_inserter( indices ), []( const auto& v ) {
            return 12 * ( static_cast<uint16_t>( v.y * oneOverForty ) ) +
                   static_cast<uint16_t>( v.x * oneOverForty );
        } );
    if ( std::any_of(
             std::cbegin( indices ), std::cend( indices ),
             [&]( uint16_t i ) { return i > 263 || filledGridMap_[i]; } ) )
        return;

    ShapeInfo::rotationSuccess( );
    for ( int i = 0; i < 4; ++i )
    {
        tetrisShape_[i].setPosition( newLocations[i] );
    }
}
#endif
