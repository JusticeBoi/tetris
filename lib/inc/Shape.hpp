#ifndef SHAPE_INCLUDED
#define SHAPE_INCLUDED

#include "IShape.hpp"
#include "macros.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

template<typename T> concept ShapeInfo = requires( T a, const std::vector<uint16_t>& currentLocation, std::vector<sf::RectangleShape>& toSetColor, const std::array<sf::Texture, 7>& textures,  const std::vector<sf::RectangleShape>& curLoc  )
{
    { T::currentRotatedState} ;
    { T::createShape( ) } ->  std::vector<sf::RectangleShape>;
    { T::startingLocation( ) } -> std::vector<uint16_t>;
    { T::rotate( currentLocation ) } -> std::vector<uint16_t>;
    { T::rotate( curLoc ) } -> std::vector<sf::Vector2f>;
    { T::setColors( toSetColor, textures ) } -> void;
    { T::rotationSuccess() } -> void;

};

template<ShapeInfo S> class Shape final : public IShape
{
  public:
    void move( int8_t right, int8_t bottom ) override;
    void move( float x, float y ) override;
    void rotate( ) override;

    Shape( std::array<uint8_t, 264>& );
    Shape( ) = delete;
    void resetRotationState( ) override;
    Shape( const Shape& s ) = delete;
    Shape( Shape&& s ) = delete;
    Shape& operator=( Shape&& s ) = delete;
    Shape& operator=( const Shape& s ) = delete;
};

template<ShapeInfo S>
Shape<S>::Shape( std::array<uint8_t, 264>& arr )
    : IShape( S::createShape( ), arr )
{
    S::setColors( tetrisShape_, textures );
};

template<ShapeInfo S>
void Shape<S>::move( int8_t right, int8_t bottom )
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
                S::currentRotatedState = 0;
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
    changeTheShadeView( );
}

template<ShapeInfo S>
void Shape<S>::move( float x, float y )
{
    using constants::oneOverForty;
    const auto positions = getPositionsOfRectangles( );
    float toRight = static_cast<float>(
        ( static_cast<int>( x - positions[0].x ) / 40 ) * 40 );
    for ( const auto& pos : positions )
    {

        const float newX = pos.x + toRight;
        const float newY = pos.y ;
        if ( newX < -0.1f || newX > 440.f )
            return;
        if ( pos.y < -39.f )
            continue;

        uint16_t posIndex = static_cast<uint16_t>(
            ( newX * oneOverForty ) + ( newY * oneOverForty ) * 12 );
        if ( filledGridMap_[posIndex] || newY > 841.f )
        {
            std::cout <<"stopped my mouse! \n";
            if ( std::abs( newY - pos.y ) > 1.f )
            {
                stopped = 1;
                oneMoreMove = 1;
                S::currentRotatedState = 0;
            }
            return;
        }
        else if ( stopped  )
        {
            return;
        }
    }
        for ( auto& rec : tetrisShape_ )
        {
            rec.move( toRight, 0.f );
        }
    changeTheShadeView( );
}
template<ShapeInfo S> void Shape<S>::resetRotationState( )
{
    S::currentRotatedState = 0;
}
template<ShapeInfo S> void Shape<S>::rotate( )
{
    using constants::oneOverForty;
    if ( stopped )
        return;
    const std::vector<sf::Vector2f> newLocations =
        S::rotate( tetrisShape_ );

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

    S::rotationSuccess( );
    for ( int i = 0; i < 4; ++i )
    {
        tetrisShape_[i].setPosition( newLocations[i] );
    }
    changeTheShadeView( );
}
#endif
