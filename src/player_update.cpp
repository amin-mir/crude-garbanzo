#include "player_update.hpp"

#include "level_update.hpp"

PlayerUpdate::PlayerUpdate(SoundEngine& se) : sound_engine_{se} {}

sf::FloatRect* PlayerUpdate::GetPositionPointer() { return &position_; }

bool* PlayerUpdate::GetGroundedPointer() { return &is_grounded_; }

InputReceiver* PlayerUpdate::GetInputReceiver() { return &input_receiver_; }

void PlayerUpdate::Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) {
    position_.width = kPlayerWidth;
    position_.height = kPlayerHeight;
    is_paused_ = level_update->GetIsPausedPointer();
}

void PlayerUpdate::HandleInput() {
    for (const sf::Event& event : input_receiver_.GetEvents()) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::D) {
                right_is_held_down_ = true;
            }
            if (event.key.code == sf::Keyboard::A) {
                left_is_held_down_ = true;
            }
            if (event.key.code == sf::Keyboard::W) {
                boost_is_held_down_ = true;
            }
            if (event.key.code == sf::Keyboard::Space) {
                space_held_down_ = true;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::D) {
                right_is_held_down_ = false;
            }
            if (event.key.code == sf::Keyboard::A) {
                left_is_held_down_ = false;
            }
            if (event.key.code == sf::Keyboard::W) {
                boost_is_held_down_ = false;
            }
            if (event.key.code == sf::Keyboard::Space) {
                space_held_down_ = false;
            }
        }
    }
    input_receiver_.ClearEvents();
}

void PlayerUpdate::Update(float elapsed_time) {
    if (!*is_paused_) {
        position_.top += gravity_ * elapsed_time;
        HandleInput();
        if (is_grounded_) {
            if (right_is_held_down_) {
                position_.left += elapsed_time * run_speed_;
            }
            if (left_is_held_down_) {
                position_.left -= elapsed_time * run_speed_;
            }
        }
        if (boost_is_held_down_) {
            position_.top -= elapsed_time * boost_speed_;
            if (right_is_held_down_) {
                position_.left += elapsed_time * run_speed_ / 2;
            }
            if (left_is_held_down_) {
                position_.left -= elapsed_time * run_speed_ / 2;
            }
        }
        if (space_held_down_ && !in_jump_ && is_grounded_) {
            sound_engine_.PlayJump();
            in_jump_ = true;
            jump_clock_.restart();
        }
        if (!space_held_down_) {
            // mInJump = false;
        }
        if (in_jump_) {
            if (jump_clock_.getElapsedTime().asSeconds() < jump_duration_ / 2) {
                // Going up
                position_.top -= jump_speed_ * elapsed_time;
            } else {
                // Going down
                position_.top += jump_speed_ * elapsed_time;
            }
            if (jump_clock_.getElapsedTime().asSeconds() > jump_duration_) {
                in_jump_ = false;
            }
            if (right_is_held_down_) {
                position_.left += elapsed_time * run_speed_;
            }
            if (left_is_held_down_) {
                position_.left -= elapsed_time * run_speed_;
            }
        }
        is_grounded_ = false;
    }
}
