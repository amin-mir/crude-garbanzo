#include "platform_update.hpp"

#include "player_update.hpp"

sf::FloatRect* PlatformUpdate::GetPositionPointer() { return &position_; }

void PlatformUpdate::Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) {
    player_position_ = player_update->GetPositionPointer();
    player_is_grounded_ = player_update->GetGroundedPointer();
}

void PlatformUpdate::Update(float elapsed_time) {
    if (position_.intersects(*player_position_)) {
        sf::Vector2f player_feet(player_position_->left + player_position_->width / 2,
                                 player_position_->top + player_position_->height);
        sf::Vector2f player_right(player_position_->left + player_position_->width,
                                  player_position_->top + player_position_->height / 2);
        sf::Vector2f player_left(player_position_->left, player_position_->top + player_position_->height / 2);
        sf::Vector2f player_head(player_position_->left + player_position_->width / 2, player_position_->top);
        if (position_.contains(player_feet)) {
            if (player_feet.y > position_.top) {
                player_position_->top = position_.top - player_position_->height;
                *player_is_grounded_ = true;
            }
        } else if (position_.contains(player_right)) {
            player_position_->left = position_.left - player_position_->width;
        } else if (position_.contains(player_left)) {
            player_position_->left = position_.left + position_.width;
        } else if (position_.contains(player_head)) {
            player_position_->top = position_.top + position_.height;
        }
    }
}
