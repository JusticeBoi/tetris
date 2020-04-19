#include "../inc/GameScreen.hpp"
#include "../inc/Game.hpp"
#include "../inc/Shape.hpp"

#include "../inc/CubeShapeInfo.hpp"
#include "../inc/LShapeInfo.hpp"
#include "../inc/LineShapeInfo.hpp"
#include "../inc/MirroredLShapeInfo.hpp"
#include "../inc/SShapeInfo.hpp"
#include "../inc/TShapeInfo.hpp"
#include "../inc/ZShapeInfo.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Text.hpp>

GameScreen::GameScreen( Game& g ) : game_( &g ){};

int GameScreen::Run( sf::RenderWindow& App )
{
    App.setPosition( sf::Vector2i{ 10, 50 } );

    bool Running = true;
    sf::Clock clock;
    static bool spawnNewShape = true;
    if ( spawnNewShape )
    {
        game_->shownObjects.push_back( game_->getRandomShape( ) );
        spawnNewShape = false;
    }
    IShape* shape = game_->shownObjects.back( ).get( );
    static bool pause = false;
    /* std::cout <<"spawnNewShape : " << spawnNewShape << '\n'; */
    sf::Vector2i grabbedOffset;
    bool grabbedWindow = false;
    while ( Running )
    {
        if ( spawnNewShape )
        {
            game_->shownObjects.push_back( game_->getRandomShape( ) );
            shape = game_->shownObjects.back( ).get( );
            spawnNewShape = false;
        }
        sf::Event event;
        while ( App.pollEvent( event ) )
        {
            switch ( event.type )
            {
                case sf::Event::KeyPressed:
                    if ( !pause )
                    {

                        if ( event.key.code == sf::Keyboard::Left )
                        {
                            shape->move( static_cast<int8_t>( -1 ),
                                         static_cast<int8_t>( 0 ) );
                        }
                        else if ( event.key.code == sf::Keyboard::Right )
                        {
                            shape->move( static_cast<int8_t>( 1 ),
                                         static_cast<int8_t>( 0 ) );
                        }
                        else if ( event.key.code == sf::Keyboard::Down )
                        {
                            shape->move( static_cast<int8_t>( 0 ),
                                         static_cast<int8_t>( 1 ) );
                        }
                        else if ( event.key.code == sf::Keyboard::Up )
                        {
                            shape->rotate( );
                        }
                    }
                    if ( event.key.code == sf::Keyboard::Escape )
                    {
                        pause = 0;
                        return 0;
                    }
                    else if ( event.key.code == sf::Keyboard::P )
                    {
                        pause = true;
                    }
                    else if ( event.key.code == sf::Keyboard::C )
                    {
                        pause = false;
                    }
                    continue;

                case sf::Event::MouseButtonPressed:
                    if ( event.mouseButton.button == sf::Mouse::Left )
                    {
                        grabbedOffset =
                            App.getPosition( ) - sf::Mouse::getPosition( );
                    }
                    else if ( !pause &&
                              event.mouseButton.button == sf::Mouse::Right )
                    {
                            shape->rotate( );
                    }
                    break;
                case sf::Event::MouseMoved:
                    {
                    if ( !pause )
                    {
                        const float x = event.mouseMove.x;
                        const float y = event.mouseMove.y;
                        shape->move( x, y );
                    }
                    break;
                }
                case sf::Event::MouseWheelScrolled: {
                    if ( !pause )
                    {
                        if ( event.mouseWheelScroll.delta < 0.f )
                        {
                            shape->moveToShadesLocation( );
                            shape->resetRotationState( );
                        }
                        break;
                    }
                }
                case sf::Event::Closed:
                    App.close( );
                    return -1;
                    break;
                default:
                    break;
            }
        }
        if ( !pause )
        {
            if ( clock.getElapsedTime( ).asMilliseconds( ) > 350 )
            {
                clock.restart( );

                if ( shape->stopped && !spawnNewShape )
                {
                    shape->showShade = 0;
                    std::cout << "inside\n";
                    game_->addToFilledGrids( shape );
                    spawnNewShape = true;
                    game_->checkForFullRow( );
                    Running = game_->isGameStillRunning( );
                    game_->approxMemoryConsumption( );
                    /* shape = game_->shownObjects.back( ).get( ); */
                    continue;
                }
                shape->move( static_cast<int8_t>( 0 ),
                             static_cast<int8_t>( 1 ) );
            }
        }
        App.clear( );

        grabbedWindow = sf::Mouse::isButtonPressed( sf::Mouse::Left );

        if ( grabbedWindow )
            App.setPosition( sf::Mouse::getPosition( ) + grabbedOffset );

        game_->showWorldMesh( );
        for ( const auto& s : game_->shownObjects )
            App.draw( *s );
        App.display( );
    }

    return -1;
}
