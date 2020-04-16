#ifndef GAME_SCREEN_HPP_INCLUDED
#define GAME_SCREEN_HPP_INCLUDED
#include <iostream>

#include "cScreen.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Game;
class GameScreen : public cScreen
{
  public:
    GameScreen( Game& game );
    virtual int Run( sf::RenderWindow& App ) override;

  private:
    Game* game_;

    static constexpr uint16_t alpha_max = 255 * 6;
    static constexpr uint16_t alpha_div = 6;

    uint16_t alpha_tmp = 0;
};
#endif // GAME_SCREEN
