#include "platform_graphics.hpp"

#include "platform_update.hpp"

void PlatformGraphics::Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> update, sf::IntRect tex_coords) {
    auto platform_update = std::static_pointer_cast<PlatformUpdate>(update);
    position_ = platform_update->GetPositionPointer();
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

    const sf::Vector2f tex_pos(tex_coords.left, tex_coords.top);
    const sf::Vector2f tex_size(tex_coords.width, tex_coords.height);
    canvas[vertex_start_index_].texCoords = tex_pos;
    canvas[vertex_start_index_ + 1].texCoords = tex_pos + sf::Vector2f(tex_size.x, 0);
    canvas[vertex_start_index_ + 2].texCoords = tex_pos + tex_size;
    canvas[vertex_start_index_ + 3].texCoords = tex_pos + sf::Vector2f(0, tex_size.y);
}

void PlatformGraphics::Draw(sf::VertexArray& canvas) {
    const sf::Vector2f& position = position_->getPosition();
    const sf::Vector2f& scale = position_->getSize();
    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f(scale.x, 0);
    canvas[vertex_start_index_ + 2].position = position + scale;
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f(0, scale.y);
}
