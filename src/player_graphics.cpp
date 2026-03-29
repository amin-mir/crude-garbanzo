#include "player_graphics.hpp"

#include <memory>

void PlayerGraphics::Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> update, sf::IntRect tex_coords) {
    player_update_ = std::static_pointer_cast<PlayerUpdate>(update);
    position_ = player_update_->GetPositionPointer();
    animator_ = new Animator(tex_coords.left, tex_coords.top,
                             6,  // 6 frames
                             tex_coords.width * 6, tex_coords.height,
                             12);  // FPS
    // Get the first frame of animation
    section_to_draw_ = animator_->GetCurrentFrame(false);
    standing_still_section_to_draw_ = animator_->GetCurrentFrame(false);
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);
}

void PlayerGraphics::Draw(sf::VertexArray& canvas) {
    const sf::Vector2f position = position_->getPosition();
    const sf::Vector2f scale = position_->getSize();
    canvas[vertex_start_index_].position = position;
    canvas[vertex_start_index_ + 1].position = position + sf::Vector2f(scale.x, 0);
    canvas[vertex_start_index_ + 2].position = position + scale;
    canvas[vertex_start_index_ + 3].position = position + sf::Vector2f(0, scale.y);
    if (player_update_->right_is_held_down_ && !player_update_->in_jump_ && !player_update_->boost_is_held_down_ &&
        player_update_->is_grounded_) {
        section_to_draw_ = animator_->GetCurrentFrame(false);
    }
    if (player_update_->left_is_held_down_ && !player_update_->in_jump_ && !player_update_->boost_is_held_down_ &&
        player_update_->is_grounded_) {
        section_to_draw_ = animator_->GetCurrentFrame(true);
        // reversed
    } else {
        // Test the players facing position
        // in case it changed while jumping or boosting
        // This value is used in the final animation option
        if (player_update_->left_is_held_down_) {
            last_facing_right_ = false;
        } else {
            last_facing_right_ = true;
        }
    }

    const int tex_left = section_to_draw_->left;
    const int tex_top = section_to_draw_->top;
    const int tex_width = section_to_draw_->width;
    const int tex_height = section_to_draw_->height;
    if (player_update_->right_is_held_down_ && !player_update_->in_jump_ && !player_update_->boost_is_held_down_) {
        canvas[vertex_start_index_].texCoords.x = tex_left;
        canvas[vertex_start_index_].texCoords.y = tex_top;
        canvas[vertex_start_index_ + 1].texCoords.x = tex_left + tex_width;
        canvas[vertex_start_index_ + 1].texCoords.y = tex_top;
        canvas[vertex_start_index_ + 2].texCoords.x = tex_left + tex_width;
        canvas[vertex_start_index_ + 2].texCoords.y = tex_top + tex_height;
        canvas[vertex_start_index_ + 3].texCoords.x = tex_left;
        canvas[vertex_start_index_ + 3].texCoords.y = tex_top + tex_height;
    } else if (player_update_->left_is_held_down_ && !player_update_->in_jump_ &&
               !player_update_->boost_is_held_down_) {
        canvas[vertex_start_index_].texCoords.x = tex_left;
        canvas[vertex_start_index_].texCoords.y = tex_top;
        canvas[vertex_start_index_ + 1].texCoords.x = tex_left - tex_width;
        canvas[vertex_start_index_ + 1].texCoords.y = tex_top;
        canvas[vertex_start_index_ + 2].texCoords.x = tex_left - tex_width;
        canvas[vertex_start_index_ + 2].texCoords.y = tex_top + tex_height;
        canvas[vertex_start_index_ + 3].texCoords.x = tex_left;
        canvas[vertex_start_index_ + 3].texCoords.y = tex_top + tex_height;
    } else if (player_update_->right_is_held_down_ && player_update_->boost_is_held_down_) {
        canvas[vertex_start_index_].texCoords.x = kBoostTexLeft;
        canvas[vertex_start_index_].texCoords.y = kBoostTexTop;
        canvas[vertex_start_index_ + 1].texCoords.x = kBoostTexLeft + kBoostTexWidth;
        canvas[vertex_start_index_ + 1].texCoords.y = kBoostTexTop;
        canvas[vertex_start_index_ + 2].texCoords.x = kBoostTexLeft + kBoostTexWidth;
        canvas[vertex_start_index_ + 2].texCoords.y = kBoostTexTop + kBoostTexHeight;
        canvas[vertex_start_index_ + 3].texCoords.x = kBoostTexLeft;
        canvas[vertex_start_index_ + 3].texCoords.y = kBoostTexTop + kBoostTexHeight;
    } else if (player_update_->left_is_held_down_ && player_update_->boost_is_held_down_) {
        canvas[vertex_start_index_].texCoords.x = kBoostTexLeft + kBoostTexWidth;
        canvas[vertex_start_index_].texCoords.y = kBoostTexTop;
        canvas[vertex_start_index_ + 1].texCoords.x = kBoostTexLeft;
        canvas[vertex_start_index_ + 1].texCoords.y = kBoostTexTop;
        canvas[vertex_start_index_ + 2].texCoords.x = kBoostTexLeft;
        canvas[vertex_start_index_ + 2].texCoords.y = kBoostTexTop + kBoostTexHeight;
        canvas[vertex_start_index_ + 3].texCoords.x = kBoostTexLeft + kBoostTexWidth;
        canvas[vertex_start_index_ + 3].texCoords.y = kBoostTexTop + kBoostTexHeight;
    } else if (player_update_->boost_is_held_down_) {
        canvas[vertex_start_index_].texCoords.x = kBoostTexLeft;
        canvas[vertex_start_index_].texCoords.y = kBoostTexTop;
        canvas[vertex_start_index_ + 1].texCoords.x = kBoostTexLeft + kBoostTexWidth;
        canvas[vertex_start_index_ + 1].texCoords.y = kBoostTexTop;
        canvas[vertex_start_index_ + 2].texCoords.x = kBoostTexLeft + kBoostTexWidth;
        canvas[vertex_start_index_ + 2].texCoords.y = kBoostTexTop + kBoostTexHeight;
        canvas[vertex_start_index_ + 3].texCoords.x = kBoostTexLeft;
        canvas[vertex_start_index_ + 3].texCoords.y = kBoostTexTop + kBoostTexHeight;
    } else {
        if (last_facing_right_) {
            canvas[vertex_start_index_].texCoords.x = standing_still_section_to_draw_->left;
            canvas[vertex_start_index_].texCoords.y = standing_still_section_to_draw_->top;
            canvas[vertex_start_index_ + 1].texCoords.x = standing_still_section_to_draw_->left + tex_width;
            canvas[vertex_start_index_ + 1].texCoords.y = standing_still_section_to_draw_->top;
            canvas[vertex_start_index_ + 2].texCoords.x = standing_still_section_to_draw_->left + tex_width;
            canvas[vertex_start_index_ + 2].texCoords.y = standing_still_section_to_draw_->top + tex_height;
            canvas[vertex_start_index_ + 3].texCoords.x = standing_still_section_to_draw_->left;
            canvas[vertex_start_index_ + 3].texCoords.y = standing_still_section_to_draw_->top + tex_height;
        } else {
            canvas[vertex_start_index_].texCoords.x = standing_still_section_to_draw_->left + tex_width;
            canvas[vertex_start_index_].texCoords.y = standing_still_section_to_draw_->top;
            canvas[vertex_start_index_ + 1].texCoords.x = standing_still_section_to_draw_->left;
            canvas[vertex_start_index_ + 1].texCoords.y = standing_still_section_to_draw_->top;
            canvas[vertex_start_index_ + 2].texCoords.x = standing_still_section_to_draw_->left;
            canvas[vertex_start_index_ + 2].texCoords.y = standing_still_section_to_draw_->top + tex_height;
            canvas[vertex_start_index_ + 3].texCoords.x = standing_still_section_to_draw_->left + tex_width;
            canvas[vertex_start_index_ + 3].texCoords.y = standing_still_section_to_draw_->top + tex_height;
        }
    }
}
