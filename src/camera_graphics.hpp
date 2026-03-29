#pragma once

#include <SFML/Graphics.hpp>

#include "graphics.hpp"

class CameraGraphics : public IGraphics {
   public:
    CameraGraphics(sf::RenderWindow* window, sf::Texture* texture, sf::Vector2f view_size, sf::FloatRect viewport);
    float* GetTimeConnection();
    // From IGraphics : Component
    void Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> generic_update, sf::IntRect tex_coords) override;
    void Draw(sf::VertexArray& canvas) override;

   private:
    // For zooming the mini map
    static constexpr float kMinWidth = 640.0f;
    static constexpr float kMaxWidth = 2000.0f;

    sf::RenderWindow* window_;
    sf::View          view_;
    int               vertex_start_index_ = -999;
    sf::Texture*      texture_ = nullptr;
    sf::FloatRect*    position_ = nullptr;
    bool              is_mini_map_ = false;

    bool         bg_flipped_ = false;
    sf::Vector2f prev_pos_;
    sf::Texture  bg_texture_;
    sf::Sprite   bg1_;
    sf::Sprite   bg2_;

    // For the Time UI
    sf::Text text_;
    sf::Font font_;
    int      time_at_end_of_game_ = 0;
    float    time_ = 0;
};
