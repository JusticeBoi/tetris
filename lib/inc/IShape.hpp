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

class IShape : public sf::Drawable, public sf::Transformable
{
  public:
    IShape( const std::vector<sf::RectangleShape>& rs,  std::array<uint8_t, 264>& arr  ) : tetrisShape_( rs ), filledGridMap_(arr) {};
    uint8_t stopped = 0;
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

    IShape( ) = delete;
    IShape( const IShape& s ) = delete;
    IShape( IShape&& s ) = delete;
    IShape& operator=( IShape&& s ) = delete;
    IShape& operator=( const IShape& s ) = delete;
    virtual ~IShape( ) = default;

  protected:
    static std::array<sf::Texture, 7> textures;
    std::vector<sf::RectangleShape> tetrisShape_;
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
