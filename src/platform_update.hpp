#pragma once

#include <SFML/Graphics.hpp>

#include "update.hpp"

class PlatformUpdate : public IUpdate {
   public:
    sf::FloatRect* GetPositionPointer();

    // From IUpdate : Component
    void Update(float elapsed_time) override;
    void Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) override;

   private:
    sf::FloatRect  position_;
    sf::FloatRect* player_position_ = nullptr;
    bool*          player_is_grounded_ = nullptr;
};
