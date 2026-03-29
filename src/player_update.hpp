#pragma once

#include <SFML/Graphics.hpp>

#include "input_receiver.hpp"
#include "sound_engine.hpp"
#include "update.hpp"

class PlayerUpdate : public IUpdate {
   public:
    PlayerUpdate(SoundEngine& se);
    bool right_is_held_down_ = false;
    bool left_is_held_down_ = false;
    bool boost_is_held_down_ = false;
    bool is_grounded_;
    bool in_jump_ = false;

    sf::FloatRect* GetPositionPointer();
    bool*          GetGroundedPointer();
    void           HandleInput();
    InputReceiver* GetInputReceiver();

    // From IUpdate : Component
    void Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) override;
    void Update(float fps) override;

   private:
    static constexpr float kPlayerWidth = 20.f;
    static constexpr float kPlayerHeight = 16.f;

    SoundEngine&  sound_engine_;
    sf::FloatRect position_;
    bool*         is_paused_ = nullptr;
    float         gravity_ = 80;
    float         run_speed_ = 150;
    float         boost_speed_ = 250;
    InputReceiver input_receiver_;
    sf::Clock     jump_clock_;
    bool          space_held_down_ = false;
    float         jump_duration_ = .50;
    float         jump_speed_ = 300;
};
