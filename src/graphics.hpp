#pragma once

#include "component.hpp"
#include "update.hpp"

class IGraphics : public Component {
   public:
    virtual void Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> generic_update, sf::IntRect tex_coords) = 0;
    virtual void Draw(sf::VertexArray& canvas) = 0;
};
