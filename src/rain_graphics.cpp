#include "rain_graphics.hpp"

#include "animator.hpp"

RainGraphics::RainGraphics(sf::FloatRect* player_position, float horizontal_offset, float vertical_offset,
                           int rain_coverage_per_object) {
    player_position_ = player_position;
    horizontal_offset_ = horizontal_offset;
    vertical_offset_ = vertical_offset;
    scale_.x = rain_coverage_per_object;
    scale_.y = rain_coverage_per_object;
}

void RainGraphics::Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> update, sf::IntRect tex_coords) {
    animator_ = new Animator(tex_coords.left, tex_coords.top,
                             4,  // Frames
                             tex_coords.width * 4, tex_coords.height,
                             8  // FPS
    );
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);
}

void RainGraphics::Draw(sf::VertexArray& canvas) {
    const sf::Vector2f& position = player_position_->getPosition() -
                                   sf::Vector2f(scale_.x / 2 + horizontal_offset_, scale_.y / 2 + vertical_offset_);
    // Move the rain to keep up with the player
    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f(scale_.x, 0);
    canvas[vertex_start_index_ + 2].position = position + scale_;
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f(0, scale_.y);
    // Cycle through the frames
    frame_rect_ = animator_->GetCurrentFrame(false);
    const sf::Vector2f tex_pos(frame_rect_->left, frame_rect_->top);
    const sf::Vector2f tex_size(frame_rect_->width, frame_rect_->height);
    canvas[vertex_start_index_].texCoords     = tex_pos;
    canvas[vertex_start_index_ + 1].texCoords = tex_pos + sf::Vector2f(tex_size.x, 0);
    canvas[vertex_start_index_ + 2].texCoords = tex_pos + tex_size;
    canvas[vertex_start_index_ + 3].texCoords = tex_pos + sf::Vector2f(0, tex_size.y);
}
