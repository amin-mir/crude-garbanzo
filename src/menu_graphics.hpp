#pragma once

#include <SFML/Graphics.hpp>

#include "graphics.hpp"

class MenuGraphics : public IGraphics {
   public:
    // From IGraphics : Component
    void Draw(sf::VertexArray& canvas) override;
    void Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> generic_update, sf::IntRect tex_coords) override;

   private:
    sf::FloatRect* menu_position_ = nullptr;
    int            vertex_start_index_;
    bool*          game_over_;
    bool           current_status_ = false;
    int            tex_left_;
    int            tex_top_;
    int            tex_width_;
    int            tex_height_;
};
