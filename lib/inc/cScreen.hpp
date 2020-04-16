#ifndef CSCREEN_HPP_INCLUDED
#define CSCREEN_HPP_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class cScreen
{
public :
    enum NowPlaying : uint_fast8_t
    {
        NOTHING = 0,
        PLAYTIME = 1,
    };
    enum class Hover : uint8_t
    {
        EXIT = 0,
        CONTINUE = 1,
        PLAY = 2,
        OUT = 3,
        TIP = 4,
        EXITMENU = 5
    };
    virtual int Run (sf::RenderWindow &App) = 0;
    virtual int loadFromFile (const std::string& str) ; 
    bool finished_;
    virtual void init();
    virtual ~cScreen() = default;
protected:
    
    sf::Texture texture;
	sf::Sprite sprite;
    
};

#endif
