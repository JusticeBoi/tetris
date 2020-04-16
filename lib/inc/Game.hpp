#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Shape.hpp"
#include "WorldMesh.hpp"
#include "screens.hpp"

#include "CubeShapeInfo.hpp"
#include "LShapeInfo.hpp"
#include "LineShapeInfo.hpp"
#include "MirroredLShapeInfo.hpp"
#include "SShapeInfo.hpp"
#include "TShapeInfo.hpp"
#include "ZShapeInfo.hpp"

#include <memory>
#include <random>
#include <variant>


class Game
{
  public:
    Game( ) = default;
    void run( );
    void showWorldMesh( ) const;
    const WorldMesh& getWorldMesh( );
    void saveStoppedShapeLocation( const IShape* s );
    bool isGameStillRunning( ) const;

    std::unique_ptr<IShape> getRandomShape( );
    void checkForFullRow( int = 263 );
    void eraseFullRow( int );

    std::vector<std::unique_ptr<IShape>> shownObjects;
    void addToFilledGrids( const IShape* );
    const std::bitset<264>& getFilledGrid( ) const;
    void freeHiddenShapes( );
    void checkIfShownAndFilledGridsIsTheSame( );
    void approxMemoryConsumption( );
    void showGrid( );
    void updateFilledGridsFromVisual( );

  private:
    std::array<uint8_t, 264> filledGridMap_{};
    void fillShapeVector( );
    WorldMesh wMesh_;
    sf::RenderWindow* rWindow_;
};

#endif
