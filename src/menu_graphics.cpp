#include "menu_graphics.hpp"

#include "menu_update.hpp"

void MenuGraphics::Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> update, sf::IntRect tex_coords) {
    auto menu_update = std::static_pointer_cast<MenuUpdate>(update);
    menu_position_ = menu_update->GetPositionPointer();
    game_over_ = menu_update->GetGameOverPointer();
    current_status_ = *game_over_;
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

    tex_left_ = tex_coords.left;
    tex_top_ = tex_coords.top;
    tex_width_ = tex_coords.width;
    tex_height_ = tex_coords.height;
    canvas[vertex_start_index_].texCoords.x = tex_left_;
    canvas[vertex_start_index_].texCoords.y = tex_top_ + tex_height_;
    canvas[vertex_start_index_ + 1].texCoords.x = tex_left_ + tex_width_;
    canvas[vertex_start_index_ + 1].texCoords.y = tex_top_ + tex_height_;
    canvas[vertex_start_index_ + 2].texCoords.x = tex_left_ + tex_width_;
    canvas[vertex_start_index_ + 2].texCoords.y = tex_top_ + tex_height_ + tex_height_;
    canvas[vertex_start_index_ + 3].texCoords.x = tex_left_;
    canvas[vertex_start_index_ + 3].texCoords.y = tex_top_ + tex_height_ + tex_height_;
}

void MenuGraphics::Draw(sf::VertexArray& canvas) {
    // current status has just switched to game over
    if (*game_over_ && !current_status_) {
        // Each v coordinate is doubled to
        // reference the texture below
        current_status_ = *game_over_;
        canvas[vertex_start_index_].texCoords.x = tex_left_;
        canvas[vertex_start_index_].texCoords.y = tex_top_ + tex_height_;
        canvas[vertex_start_index_ + 1].texCoords.x = tex_left_ + tex_width_;
        canvas[vertex_start_index_ + 1].texCoords.y = tex_top_ + tex_height_;
        canvas[vertex_start_index_ + 2].texCoords.x = tex_left_ + tex_width_;
        canvas[vertex_start_index_ + 2].texCoords.y = tex_top_ + tex_height_ + tex_height_;
        canvas[vertex_start_index_ + 3].texCoords.x = tex_left_;
        canvas[vertex_start_index_ + 3].texCoords.y = tex_top_ + tex_height_ + tex_height_;
    } else if (!*game_over_ && current_status_) {
        current_status_ = *game_over_;
        canvas[vertex_start_index_].texCoords.x = tex_left_;
        canvas[vertex_start_index_].texCoords.y = tex_top_;
        canvas[vertex_start_index_ + 1].texCoords.x = tex_left_ + tex_width_;
        canvas[vertex_start_index_ + 1].texCoords.y = tex_top_;
        canvas[vertex_start_index_ + 2].texCoords.x = tex_left_ + tex_width_;
        canvas[vertex_start_index_ + 2].texCoords.y = tex_top_ + tex_height_;
        canvas[vertex_start_index_ + 3].texCoords.x = tex_left_;
        canvas[vertex_start_index_ + 3].texCoords.y = tex_top_ + tex_height_;
    }
    const sf::Vector2f& position = menu_position_->getPosition();
    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f(menu_position_->getSize().x, 0);
    canvas[vertex_start_index_ + 2].position = position + menu_position_->getSize();
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f(0, menu_position_->getSize().y);
}
