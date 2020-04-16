#include "../inc/WorldMesh.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <algorithm>
#include <iostream>


WorldMesh::WorldMesh ( ) 
{
    std::cout <<"World mesh bound : " << bound_.left << ' ' << bound_.top << ' ' << bound_.width << ' ' << bound_.height << '\n';
    mesh_.setPrimitiveType(sf::Quads);
    mesh_.resize(elX*elY*4);
    tile_.create(elSize,elSize);

    fillMeshPixels();

    tile_.update(&pixels_[0]);

    for ( size_t x = 0;  x < elX  ; ++x )
    {
        for ( size_t y = 0;  y < elY  ; ++y )
        {
            size_t index = (x + elX*y) * 4;
            sf::Vertex* quad = &mesh_[index];

            quad[0].position =
                sf::Vector2f( static_cast<float>( x * elSize ),
                              static_cast<float>( y * elSize  ) );
            quad[1].position =
                sf::Vector2f( static_cast<float>( ( x + 1 ) * elSize ),
                              static_cast<float>( y * elSize ) );
            quad[2].position =
                sf::Vector2f( static_cast<float>( ( x + 1 ) * elSize ),
                              static_cast<float>( ( y + 1 ) * elSize  ) );
            quad[3].position =
                sf::Vector2f( static_cast<float>( x * elSize ),
                              static_cast<float>( ( y + 1 ) * elSize  ) );

            quad[0].texCoords = sf::Vector2f( 0.f, 0.f );
            quad[1].texCoords = sf::Vector2f( 40.f, 0.f );
            quad[2].texCoords = sf::Vector2f( 40.f, 40.f );
            quad[3].texCoords = sf::Vector2f( 0.f, 40.f );
        }
    }
}
void WorldMesh::fillMeshPixels()
{
    for ( size_t i = 0; i < elSize; ++i )
    {
        pixels_[i * 4] = 0;
        pixels_[i * 4 + 1] = 0;
        pixels_[i * 4 + 2] = 0;
        pixels_[i * 4 + 3] = 0;
        for ( size_t j = 1; j < elSize; ++j )
        {
            if ( !i )
            {
                pixels_[( i + j * elSize ) * 4] = 0;
                pixels_[( i + j * elSize ) * 4 + 1] = 0;
                pixels_[( i + j * elSize ) * 4 + 2] = 0;
                pixels_[( i + j * elSize ) * 4 + 3] = 0;
            }
            else
            {
                pixels_[( i + j * elSize ) * 4] = 255;
                pixels_[( i + j * elSize ) * 4 + 1] = 255;
                pixels_[( i + j * elSize ) * 4 + 2] = 255;
                pixels_[( i + j * elSize ) * 4 + 3] = 255;
            }
        }
    }
}
void WorldMesh::draw(sf::RenderTarget& target, sf::RenderStates states) const   
{
    states.texture = &tile_;
    target.draw(mesh_, states);

}
