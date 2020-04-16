#ifndef WORLDMESH_INCLUDED
#define WORLDMESH_INCLUDED

#include "IShape.hpp"
#include "Shape.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <bitset>

class WorldMesh : public sf::Drawable
{
  public:
    WorldMesh( );
    virtual void draw( sf::RenderTarget& target,
                       sf::RenderStates /*states*/ ) const override;
    virtual ~WorldMesh( ) = default;

    sf::FloatRect bound_{0.f, 0.f, w_, h_};

    WorldMesh( const WorldMesh& ) = delete;
    WorldMesh( WorldMesh&& ) = delete;
    const WorldMesh& operator=( const WorldMesh& ) = delete;
    const WorldMesh& operator=( WorldMesh&& ) = delete;

  private:
    static constexpr float w_ = 480.f;
    static constexpr float h_ = 880.f;

    static constexpr size_t elSize = 40;

    static constexpr size_t elX = w_ / elSize;
    static constexpr size_t elY = h_ / elSize;

    sf::VertexArray mesh_;
    sf::VertexArray lines_;

    sf::Texture tile_;
    void fillMeshPixels( );
    std::array<sf::Uint8, elSize * elSize * 4> pixels_;
};

#endif
