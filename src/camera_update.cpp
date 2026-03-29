#include "camera_update.hpp"

#include "player_update.hpp"

sf::FloatRect* CameraUpdate::GetPositionPointer() { return &position_; }

void CameraUpdate::Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) {
    player_position_ = player_update->GetPositionPointer();
}

InputReceiver* CameraUpdate::GetInputReceiver() {
    input_receiver_ = new InputReceiver;
    receives_input_ = true;
    return input_receiver_;
}

void CameraUpdate::HandleInput() {
    position_.width = 1.0f;
    for (const sf::Event& event : input_receiver_->GetEvents()) {
        // Handle mouse wheel event for zooming
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                // Accumulate the zoom factor based on delta
                position_.width *= (event.mouseWheelScroll.delta > 0) ? 0.95f : 1.05f;
            }
        }
    }
    input_receiver_->ClearEvents();
}

void CameraUpdate::Update(float elapsed_time) {
    if (receives_input_) {
        HandleInput();
    } else {
        position_.width = 1;
    }
    position_.left = player_position_->left;
    position_.top = player_position_->top;
}
