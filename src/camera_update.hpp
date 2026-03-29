#pragma once

#include <SFML/Graphics.hpp>

#include "input_receiver.hpp"
#include "update.hpp"

class CameraUpdate : public IUpdate {
   public:
    sf::FloatRect* GetPositionPointer();
    void           HandleInput();
    InputReceiver* GetInputReceiver();
    // From IUpdate : Component
    void Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) override;
    void Update(float elapsed_time) override;

   private:
    sf::FloatRect  position_;
    sf::FloatRect* player_position_;
    bool           receives_input_ = false;
    InputReceiver* input_receiver_ = nullptr;
};
