#pragma once

#include "animator.hpp"
#include "graphics.hpp"
#include "player_update.hpp"

// Why this forward declaration here?
// class PlayerUpdate;

class PlayerGraphics : public IGraphics {
   public:
    // From IGraphics : Component
    void Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> generic_update, sf::IntRect tex_coords) override;
    void Draw(sf::VertexArray& canvas) override;

   private:
    static constexpr int kBoostTexLeft = 536;
    static constexpr int kBoostTexTop = 0;
    static constexpr int kBoostTexWidth = 69;
    static constexpr int kBoostTexHeight = 100;

    sf::FloatRect*                position_ = nullptr;
    int                           vertex_start_index_ = -999;
    sf::IntRect*                  section_to_draw_ = new sf::IntRect;
    sf::IntRect*                  standing_still_section_to_draw_ = new sf::IntRect;
    std::shared_ptr<PlayerUpdate> player_update_;
    bool                          last_facing_right_ = true;
    Animator*                     animator_;
};
