#include "../inc/screens.hpp"
#include "Game.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

void MenuScreen::init( )
{
    playing = NowPlaying::NOTHING;
    wasPlaying = NowPlaying::NOTHING;
}
MenuScreen::MenuScreen( Game& g )
    : game_( &g ), playing( NowPlaying::NOTHING ),
      wasPlaying( NowPlaying::NOTHING )
{}
int MenuScreen::Run( sf::RenderWindow& App )
{
    sf::Event Event;
    bool Running = true;
    int alpha = 0;

    sf::Font Font;
    sf::Text Play;
    sf::Text Exit;
    sf::Text Continue;

    if ( !loadFromFile( "../themes/tetris_theme.png" ) )
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return ( -1 );
    }
    sprite.setColor( sf::Color( 255, 255, 255, alpha ) );
    if ( !Font.loadFromFile( "../fonts/Inconsolata.ttf" ) )
    {
        std::cerr << "Error loading Inconsolata.ttf" << std::endl;
        return ( -1 );
    }

    Play.setFont( Font );
    Play.setCharacterSize( 40 );
    Play.setString( "Start" );
    Play.setPosition( {190.f, 360.f} );

    Exit.setFont( Font );
    Exit.setCharacterSize( 40 );
    Exit.setString( "Exit" );
    Exit.setPosition( {190.f, 420.f} );

    Continue.setFont( Font );
    Continue.setCharacterSize( 40 );
    Continue.setString( "Continue" );
    Continue.setPosition( {190.f, 360.f} );

    Hover hover = Hover::OUT;

    if ( playing != NowPlaying::NOTHING )
    {
        alpha = alpha_max;
    }

    sf::Vector2i grabbedOffset;
    bool grabbedWindow = false;
    while ( Running )
    {
        // Verifying events
        while ( App.pollEvent( Event ) )
        {
            switch ( Event.type )
            {
                case sf::Event::Closed:
                    return -1;
                case sf::Event::MouseButtonPressed: {
                    if ( Event.mouseButton.button == sf::Mouse::Left )
                    {
                        sf::Vector2f mapped = App.mapPixelToCoords(
                            {Event.mouseButton.x, Event.mouseButton.y} );
                        if ( Exit.getGlobalBounds( ).contains( mapped ) )
                        {
                            return -1;
                        }
                        if ( playing != NowPlaying::NOTHING )
                        {
                            if ( Continue.getGlobalBounds( ).contains(
                                     mapped ) )
                            {
                                playing = wasPlaying;
                                return playing;
                            }
                        }
                        else if ( Play.getGlobalBounds( ).contains( mapped ) )
                        {
                            playing = NowPlaying::PLAYTIME;
                            wasPlaying = playing;
                            std::cout << "retuning 1 \n";
                            return 1;
                        }
                        grabbedOffset =
                            App.getPosition( ) - sf::Mouse::getPosition( );
                    }
                    break;
                }
                case sf::Event::MouseMoved: {
                    sf::Vector2f mapped = App.mapPixelToCoords(
                        {Event.mouseMove.x, Event.mouseMove.y} );
                    if ( Exit.getGlobalBounds( ).contains( mapped ) )
                    {
                        hover = Hover::EXIT;
                    }
                    else if ( playing == NowPlaying::NOTHING )
                    {
                        if ( Play.getGlobalBounds( ).contains( mapped ) )
                        {
                            hover = Hover::PLAY;
                        }
                    }
                    else if ( Continue.getGlobalBounds( ).contains( mapped ) )
                    {
                        hover = Hover::CONTINUE;
                    }
                    else
                        hover = Hover::OUT;

                    break;
                }
                default:
                    break;
            }
        }
        // When getting at alpha_max, we stop modifying the sprite
        if ( alpha < alpha_max )
        {
            alpha += 15;
        }
        sprite.setColor( sf::Color( 255, 255, 255, alpha / alpha_div ) );
        switch ( hover )
        {
            case Hover::EXIT: {
                Play.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                Continue.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                Exit.setFillColor( sf::Color( 255, 0, 0, 255 ) );
                break;
            }
            case Hover::PLAY: {
                Play.setFillColor( sf::Color( 255, 0, 0, 255 ) );
                Continue.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                Exit.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                break;
            }
            case Hover::CONTINUE: {
                Play.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                Continue.setFillColor( sf::Color( 255, 0, 0, 255 ) );
                Exit.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                break;
            }
            case Hover::EXITMENU: {
                Play.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                Continue.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                Exit.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                break;
            }
            case Hover::OUT: {
                Play.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                Continue.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                Exit.setFillColor( sf::Color( 255, 255, 255, 255 ) );
                break;
            }
        }
        // Clearing screen
        App.clear( );

        grabbedWindow = sf::Mouse::isButtonPressed( sf::Mouse::Left );
        if ( grabbedWindow )
            App.setPosition( sf::Mouse::getPosition( ) + grabbedOffset );
        // Drawing
        App.draw( sprite );
        if ( alpha == alpha_max )
        {
            if ( playing )
            {
                App.draw( Continue );
            }
            else
            {
                App.draw( Play );
            }
            App.draw( Exit );
        }
        App.display( );
    }

    // Never reaching this point normally, but just in case, exit the
    // application
    return ( -1 );
}

