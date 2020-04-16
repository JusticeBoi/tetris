#ifndef MENUSCREEN_HPP_INCLUDED
#define MENUSCREEN_HPP_INCLUDED

#include "cScreen.hpp"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

class Game;
class MenuScreen : public cScreen
{
  private:
    using cScreen::NowPlaying;

    static constexpr uint16_t alpha_max = 255 * 6;
    static constexpr uint16_t alpha_div = 6;
    void init( ) override;

    Game* game_;

  public:
    MenuScreen( Game& g );
    NowPlaying playing;
    NowPlaying wasPlaying;
    virtual int Run( sf::RenderWindow& App ) override;
};
#endif
