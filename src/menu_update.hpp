#pragma once

#include <SFML/Graphics.hpp>

#include "input_receiver.hpp"
#include "sound_engine.hpp"
#include "update.hpp"

class MenuUpdate : public IUpdate {
   public:
    MenuUpdate(sf::RenderWindow* window, SoundEngine& se);
    sf::FloatRect* GetPositionPointer();
    bool*          GetGameOverPointer();
    InputReceiver* GetInputReceiver();

    // From IUpdate : Component
    void Update(float elapsed_time) override;
    void Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) override;

   private:
    void              HandleInput();
    sf::FloatRect     position_;
    InputReceiver     input_receiver_;
    sf::FloatRect*    player_position_ = nullptr;
    bool              is_visible_ = false;
    bool*             is_paused_;
    bool              game_over_;
    sf::RenderWindow* window_;
    SoundEngine&      sound_engine_;
};
