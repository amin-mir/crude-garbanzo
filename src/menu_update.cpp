#include "menu_update.hpp"

#include "level_update.hpp"
#include "player_update.hpp"
#include "sound_engine.hpp"

MenuUpdate::MenuUpdate(sf::RenderWindow* window, SoundEngine& se) : sound_engine_{se} {
    window_ = window;
}

sf::FloatRect* MenuUpdate::GetPositionPointer() {
    return &position_;
}

bool* MenuUpdate::GetGameOverPointer() {
    return &game_over_;
}

InputReceiver* MenuUpdate::GetInputReceiver() {
    return &input_receiver_;
}

void MenuUpdate::Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) {
    player_position_ = player_update->GetPositionPointer();
    is_paused_ = level_update->GetIsPausedPointer();
    position_.height = 75;
    position_.width = 75;
    sound_engine_.StartMusic();
    sound_engine_.PauseMusic();
}

void MenuUpdate::HandleInput() {
    for (const sf::Event& event : input_receiver_.GetEvents()) {
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::F1 && is_visible_) {
                if (sound_engine_.IsPlaying()) {
                    sound_engine_.StopMusic();
                }
                window_->close();
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                is_visible_ = !is_visible_;
                *is_paused_ = !*is_paused_;
                if (game_over_) {
                    game_over_ = false;
                }
                if (!*is_paused_) {
                    sound_engine_.ResumeMusic();
                    sound_engine_.PlayClick();
                }
                if (*is_paused_) {
                    sound_engine_.PauseMusic();
                    sound_engine_.PlayClick();
                }
            }
        }
    }
    input_receiver_.ClearEvents();
}

void MenuUpdate::Update(float elapsed_time) {
    HandleInput();
    if (*is_paused_ && !is_visible_)  // Game over
    {
        is_visible_ = true;
        game_over_ = true;
    }
    if (is_visible_) {
        // Follow the player
        position_.left = player_position_->getPosition().x - position_.width / 2;
        position_.top = player_position_->getPosition().y - position_.height / 2;
    } else {
        position_.left = -999;
        position_.top = -999;
    }
}
