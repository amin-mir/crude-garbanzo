#pragma once

#include <SFML/Graphics.hpp>

#include "graphics.hpp"

class PlatformGraphics : public IGraphics {
   public:
    // From IGraphics : Component
    void Draw(sf::VertexArray& canvas) override;
    void Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> generic_update, sf::IntRect tex_coords) override;

   private:
    sf::FloatRect* position_           = nullptr;
    int            vertex_start_index_ = -1;
};
