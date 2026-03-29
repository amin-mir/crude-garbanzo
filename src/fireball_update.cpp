#include "fireball_update.hpp"

#include "player_update.hpp"

FireballUpdate::FireballUpdate(bool* is_paused, SoundEngine& sound_engine, std::mt19937& rng)
    : sound_engine_{sound_engine}, rng_{rng}, is_paused_{is_paused} {
    launch_delay_ = Rand(kMinPause, kMaxPause);
}

FireballUpdate::Direction* FireballUpdate::GetDirectionPointer() {
    return &direction_;
}

sf::FloatRect* FireballUpdate::GetPositionPointer() {
    return &position_;
}

void FireballUpdate::Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) {
    player_position_ = player_update->GetPositionPointer();
    position_.top  = Rand(player_position_->top - spawn_radius_, player_position_->top + spawn_radius_);
    position_.left = player_position_->left - Rand(200, 400);
    position_.width  = 10;
    position_.height = 10;
}

int FireballUpdate::Rand(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng_);
}

void FireballUpdate::Update(float elapsed_time) {
    if (!*is_paused_) {
        if (!waiting_to_launch_) {
            float dir = static_cast<float>(direction_);
            position_.left += speed_ * dir * elapsed_time;
            float distance = dir * (position_.left - player_position_->left);
            if (distance > range_) {
                waiting_to_launch_ = true;
                launch_timer_.restart();
                direction_ = Rand(0, 1) ? Direction::Right : Direction::Left;
                position_.top = Rand(player_position_->top - spawn_radius_, player_position_->top + spawn_radius_);
                launch_delay_ = Rand(kMinPause, kMaxPause);
            }
            // Has it hit the player
            if (player_position_->intersects(position_)) {
                // Knock the player down
                player_position_->top = player_position_->top + player_position_->height * 2;
            }
        } else {
            if (launch_timer_.getElapsedTime().asSeconds() > launch_delay_) {
                waiting_to_launch_ = false;
                sound_engine_.PlayFireballLaunch(player_position_->getPosition(), position_.getPosition());
            }
        }
    }
}