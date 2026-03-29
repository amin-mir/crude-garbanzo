#include "fireball_graphics.hpp"

void FireballGraphics::Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> update, sf::IntRect tex_coords) {
    fireball_update_ = std::static_pointer_cast<FireballUpdate>(update);
    position_ = fireball_update_->GetPositionPointer();
    direction_ = fireball_update_->GetDirectionPointer();
    animator_ = new Animator(tex_coords.left, tex_coords.top, 3, tex_coords.width * 3, tex_coords.height, 6);

    current_frame_ = animator_->GetCurrentFrame(false);
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

    const sf::Vector2f tex_pos(tex_coords.getPosition());
    const sf::Vector2f tex_size(tex_coords.getSize());
    SetTexCoords(canvas, tex_pos, tex_size, FireballUpdate::Direction::Right);
}

void FireballGraphics::Draw(sf::VertexArray& canvas) {
    const sf::Vector2f position = position_->getPosition();
    const sf::Vector2f scale = position_->getSize();
    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f(scale.x, 0);
    canvas[vertex_start_index_ + 2].position = position + scale;
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f(0, scale.y);

    current_frame_ = animator_->GetCurrentFrame(*direction_ == FireballUpdate::Direction::Left);
    const sf::Vector2f tex_pos(current_frame_->getPosition());
    const sf::Vector2f tex_size(current_frame_->getSize());
    SetTexCoords(canvas, tex_pos, tex_size, *direction_);
}

void FireballGraphics::SetTexCoords(sf::VertexArray& canvas, sf::Vector2f pos, sf::Vector2f size,
                                    FireballUpdate::Direction dir) {
    float multiplier = static_cast<float>(dir);
    canvas[vertex_start_index_].texCoords = pos;
    canvas[vertex_start_index_ + 1].texCoords = pos + sf::Vector2f(multiplier * size.x, 0);
    canvas[vertex_start_index_ + 2].texCoords = pos + sf::Vector2f(multiplier * size.x, size.y);
    canvas[vertex_start_index_ + 3].texCoords = pos + sf::Vector2f(0, size.y);
}