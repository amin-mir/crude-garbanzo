#pragma once

#include "animator.hpp"
#include "fireball_update.hpp"
#include "graphics.hpp"

class FireballGraphics : public IGraphics {
   public:
    // From IGraphics : Component
    void Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> update, sf::IntRect tex_coords) override;
    void Draw(sf::VertexArray& canvas) override;

   private:
    sf::FloatRect*                  position_ = nullptr;
    int                             vertex_start_index_ = -999;
    FireballUpdate::Direction*                      direction_ = nullptr;
    Animator*                       animator_;
    sf::IntRect*                    current_frame_;
    std::shared_ptr<FireballUpdate> fireball_update_;

    void SetTexCoords(sf::VertexArray& canvas, sf::Vector2f pos, sf::Vector2f size, FireballUpdate::Direction dir);
};