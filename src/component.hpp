#pragma once

#include <SFML/Graphics.hpp>

class Component {
   public:
    // TODO: Rename elapsed_time to fps?
    virtual void Update(float elapsed_time) {}
    virtual void Draw(sf::VertexArray& canvas) {}
    virtual ~Component() = default;
};
