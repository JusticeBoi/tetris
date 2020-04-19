#ifndef ISHAPE_INCLUDED
#define ISHAPE_INCLUDED
#include "macros.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <array>
#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>

class IShape : public sf::Drawable, public sf::Transformable
{
  public:
    IShape( const std::vector<sf::RectangleShape>& rs,
            std::array<uint8_t, 264>& arr )
        : tetrisShape_( rs ), filledGridMap_( arr )
    {
        shade_ = { sf::RectangleShape( sf::Vector2f( 40.f, 40.f ) ),
                   sf::RectangleShape( sf::Vector2f( 40.f, 40.f ) ),
                   sf::RectangleShape( sf::Vector2f( 40.f, 40.f ) ),
                   sf::RectangleShape( sf::Vector2f( 40.f, 40.f ) ) };

        shade_[0].setFillColor( sf::Color( 75, 75, 75, 75 ) );
        shade_[1].setFillColor( sf::Color( 75, 75, 75, 75 ) );
        shade_[2].setFillColor( sf::Color( 75, 75, 75, 75 ) );
        shade_[3].setFillColor( sf::Color( 75, 75, 75, 75 ) );

        shade_[0].setOutlineThickness( 0.f );
        shade_[1].setOutlineThickness( 0.f );
        shade_[2].setOutlineThickness( 0.f );
        shade_[3].setOutlineThickness( 0.f );
    };
    uint8_t stopped = 0;
    uint8_t showShade = 0;
    virtual void move( int8_t right, int8_t bottom ) = 0;
    void draw( sf::RenderTarget& target,
               sf::RenderStates states ) const override
    {
        states.transform *= getTransform( );
        for ( auto& s : tetrisShape_ )
        {
            if ( s.getPosition( ).y > -0.1f )
                target.draw( s, states );
        }
        if ( showShade && !stopped )
        {
            for ( auto& s : shade_ )
            {
                target.draw( s, states );
            }
        }
    }
    virtual void rotate( ) = 0;
    void hideAllMyRectanglesInRow( float yOfRow )
    {
        tetrisShape_.erase(
            std::remove_if( tetrisShape_.begin( ), tetrisShape_.end( ),
                            [yOfRow]( const auto& rec ) {
                                return std::abs( yOfRow -
                                                 rec.getPosition( ).y ) < 1e-2;
                            } ),
            tetrisShape_.end( ) );
    }
    static sf::Clock clock;
    void moveMyShapesOneBlockDownIfAboveRow( float yOfRow )
    {
        for ( auto& rec : tetrisShape_ )
        {
            const auto& pos = rec.getPosition( );
            if ( pos.y < yOfRow )
            {
                rec.move( 0.f, 40.f );
            }
        }
    }
    std::vector<sf::Vector2f> getPositionsOfRectangles( ) const
    {
        return {tetrisShape_[0].getPosition( ), tetrisShape_[1].getPosition( ),
                tetrisShape_[2].getPosition( ), tetrisShape_[3].getPosition( )};
    }

    std::vector<uint16_t> getIndicesOfRectangles( ) const
    {
        using constants::oneOverForty;
        std::vector<uint16_t> indices;
        indices.reserve( 4 );
        for ( const auto& rec : tetrisShape_ )
        {
            const auto& pos = rec.getPosition( );
            indices.emplace_back(
                12 * static_cast<uint16_t>( pos.y * oneOverForty ) +
                static_cast<uint16_t>( pos.x * oneOverForty ) );
        }
        return indices;
    };

    const std::vector<sf::RectangleShape>& getRectangleShapes( ) const
    {
        return tetrisShape_;
    };
    void changeTheShadeView( )
    {
        /* if ( !stopped ) */
        /* { */
            auto rectIndices = getIndicesOfRectangles( );
            if ( std::any_of( std::begin( rectIndices ),
                              std::end( rectIndices ),
                              []( const auto i ) { return i > 263; } ) )
            {
                showShade = 0;
                return;
            }
            /* for ( int i = 0; i < 22; ++i ) */
            /* { */
            /*     for ( int j = 0; j < 12; ++j ) */
            /*     { */
            /*         std::cout << static_cast<unsigned int>( */
            /*                          filledGridMap_[12 * i + j] ) */
            /*                   << ' '; */
            /*     } */
            /*     std::cout << '\n'; */
            /* } */
            /*     std::cout << '\n'; */
            while ( true )
            {
                if ( std::any_of( std::begin( rectIndices ),
                                  std::end( rectIndices ),
                                  []( const auto i ) { return i > 251; } ) )
                    break;
                if ( std::any_of( std::begin( rectIndices ),
                                  std::end( rectIndices ), [&]( const auto i ) {
                                      return filledGridMap_[i + 12];
                                  } ) )
                    break;
                for ( auto& r : rectIndices )
                    r += 12;
            }

            showShade = 1;
            for ( size_t i = 0; i < 4; ++i )
            {
                auto& shape = shade_[i];
                const auto& newIndex = rectIndices[i];

                const float newY = ( newIndex / 12 ) * 40.f;
                const float newX = ( newIndex % 12 ) * 40.f;
                shape.setPosition( newX, newY );
            }
        /* } */
    }

    IShape( ) = delete;
    IShape( const IShape& s ) = delete;
    IShape( IShape&& s ) = delete;
    IShape& operator=( IShape&& s ) = delete;
    IShape& operator=( const IShape& s ) = delete;
    virtual ~IShape( ) = default;

  protected:
    static std::array<sf::Texture, 7> textures;
    std::vector<sf::RectangleShape> tetrisShape_;
    std::vector<sf::RectangleShape> shade_;
    std::array<uint8_t, 264>& filledGridMap_;
};
inline std::array<sf::Texture, 7> IShape::textures =
    []( ) -> std::array<sf::Texture, 7> {
    sf::Texture a{};
    sf::Texture b{};
    sf::Texture c{};
    sf::Texture d{};
    sf::Texture e{};
    sf::Texture f{};
    sf::Texture g{};

    if ( a.loadFromFile( "../themes/tetris_tiles.png",
                         sf::IntRect( 0, 0, 40, 40 ) ) )
    {
        std::runtime_error( "sprite error" );
    }
    b.loadFromFile( "../themes/tetris_tiles.png",
                    sf::IntRect( 40, 0, 40, 40 ) );
    c.loadFromFile( "../themes/tetris_tiles.png",
                    sf::IntRect( 80, 0, 40, 40 ) );
    d.loadFromFile( "../themes/tetris_tiles.png",
                    sf::IntRect( 120, 0, 40, 40 ) );
    e.loadFromFile( "../themes/tetris_tiles.png",
                    sf::IntRect( 160, 0, 40, 40 ) );
    f.loadFromFile( "../themes/tetris_tiles.png",
                    sf::IntRect( 200, 0, 40, 40 ) );
    g.loadFromFile( "../themes/tetris_tiles.png",
                    sf::IntRect( 240, 0, 40, 40 ) );

    return {std::move( a ), std::move( b ), std::move( c ), std::move( d ),
            std::move( e ), std::move( f ), std::move( g )};
}( );
inline sf::Clock IShape::clock = sf::Clock( );

#endif
