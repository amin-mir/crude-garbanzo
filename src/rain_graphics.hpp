#pragma once

#include <SFML/Graphics.hpp>

#include "graphics.hpp"

class Animator;

class RainGraphics : public IGraphics {
   public:
    RainGraphics(sf::FloatRect* player_position, float horizontal_offset, float vertical_offset,
                 int rain_coverage_per_object);

    // From IGraphics : Component
    void Draw(sf::VertexArray& canvas) override;
    void Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> generic_update, sf::IntRect tex_coords) override;

   private:
    sf::FloatRect* player_position_;
    int            vertex_start_index_;
    sf::Vector2f   scale_;
    float          horizontal_offset_;
    float          vertical_offset_;
    Animator*      animator_;
    sf::IntRect*   frame_rect_;
};