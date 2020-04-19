#include "../inc/Game.hpp"
#include "../inc/macros.h"
#include "WorldMesh.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <memory>


void Game::run( )
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow App( sf::VideoMode( 480u, 880u ), "Tetris" );
    App.setFramerateLimit( 80 );
    rWindow_ = &App;

    int screen = 0;
    std::vector<cScreen*> Screens;

    MenuScreen s0( *this );
    Screens.push_back( &s0 );
    GameScreen game( *this );
    Screens.push_back( &game );

    while ( screen >= 0 )
    {
        screen = Screens[screen]->Run( App );
    }

}
void Game::showWorldMesh( ) const { rWindow_->draw( wMesh_ ); }
void Game::addToFilledGrids( const IShape* shape )
{

    const auto indices = shape->getIndicesOfRectangles( );
    for ( const uint16_t i : indices )
    {
        if ( i < 264 )
            filledGridMap_[i] = 1;
    }
}
const WorldMesh& Game::getWorldMesh( ) { return wMesh_; }
std::unique_ptr<IShape> Game::getRandomShape( )
{
    static std::random_device r;
    static std::default_random_engine rng{r( )};
    static std::vector<uint8_t> counter{0, 1, 2, 3, 4, 5, 6};
    if ( !shownObjects.size( ) )
    {
        std::shuffle( counter.begin( ), counter.end( ), rng );
    }
    static uint8_t index = 0;
    if ( counter[index] == 0 )
    {
        ++index;
        return std::make_unique<Shape<CubeShapeInfo>>( filledGridMap_ );
    }
    else if ( counter[index] == 1 )
    {
        ++index;
        return std::make_unique<Shape<LShapeInfo>>( filledGridMap_ );
    }
    else if ( counter[index] == 2 )
    {
        ++index;
        return std::make_unique<Shape<MirroredLShapeInfo>>( filledGridMap_ );
    }
    else if ( counter[index] == 3 )
    {
        ++index;
        return std::make_unique<Shape<LineShapeInfo>>( filledGridMap_ );
    }
    else if ( counter[index] == 4 )
    {
        ++index;
        return std::make_unique<Shape<SShapeInfo>>( filledGridMap_ );
    }
    else if ( counter[index] == 5 )
    {
        ++index;
        return std::make_unique<Shape<ZShapeInfo>>( filledGridMap_ );
    }
    else
    {
        index = 0;
        std::shuffle( counter.begin( ), counter.end( ), rng );
        return std::make_unique<Shape<TShapeInfo>>( filledGridMap_ );
    }
}
void Game::updateFilledGridsFromVisual( )
{
    std::array<uint8_t, 264> filledGridFromVisual{};

    for ( const auto& shape : shownObjects )
    {
        const std::vector<uint16_t> indices = shape->getIndicesOfRectangles( );
        for ( const auto& i : indices )
            filledGridFromVisual[i] = 1;
    }
    filledGridMap_ = std::move( filledGridFromVisual );
}
void Game::eraseFullRow( int i )
{
    const float yOfRow = ( i / 12 ) * 40.f;
    for ( const auto& rec : shownObjects )
    {
        rec->hideAllMyRectanglesInRow( yOfRow );
        rec->moveMyShapesOneBlockDownIfAboveRow( yOfRow );
    }
    updateFilledGridsFromVisual( );
    freeHiddenShapes( );
}
void Game::checkForFullRow( int Max )
{

    for ( int i = Max; i >= 0; i -= 12 )
    {
        if ( unlikely( filledGridMap_[i] && filledGridMap_[i - 1] &&
                       filledGridMap_[i - 2] && filledGridMap_[i - 3] &&
                       filledGridMap_[i - 4] && filledGridMap_[i - 5] &&
                       filledGridMap_[i - 6] && filledGridMap_[i - 7] &&
                       filledGridMap_[i - 8] && filledGridMap_[i - 9] &&
                       filledGridMap_[i - 10] && filledGridMap_[i - 11] ) )
        {
            eraseFullRow( i );
            checkForFullRow( i );
        }
    }
}
void Game::freeHiddenShapes( )
{
    shownObjects.erase(
        std::remove_if( shownObjects.begin( ), shownObjects.end( ),
                        []( const auto& obj ) {
                            return !obj->getRectangleShapes( ).size( );
                        } ),
        shownObjects.end( ) );
}
void Game::approxMemoryConsumption( )
{
    double memoryMB =
        static_cast<double>( sizeof( Game ) + sizeof( sf::RenderWindow ) +
                             ( sizeof( IShape ) + 8 ) * shownObjects.size( ) +
                             sizeof( sf::Clock ) * 3 + sizeof( sf::Text ) +
                             sizeof( sf::Font ) + sizeof( sf::Texture ) +
                             sizeof( sf::Sprite ) ) /
        1024.;
    std::cout << " approx memory overhead : " << memoryMB << " mbs. \n";
}
bool Game::isGameStillRunning( ) const
{
    return ( unlikely( filledGridMap_[5] || filledGridMap_[6] ) ? false
                                                                : true );
}
