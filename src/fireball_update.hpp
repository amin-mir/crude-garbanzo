#pragma once

#include <SFML/Graphics.hpp>
#include <random>

#include "sound_engine.hpp"
#include "update.hpp"

class FireballUpdate : public IUpdate {
   public:
    enum class Direction { Left = -1, Right = 1 };

   private:
    static constexpr int kMaxPause = 6;
    static constexpr int kMinPause = 1;

    sf::FloatRect  position_;
    sf::FloatRect* player_position_;
    bool*          is_paused_ = nullptr;
    float          speed_ = 250;
    float          range_ = 900;
    int            spawn_radius_ = 250;
    bool           waiting_to_launch_ = true;
    sf::Clock      launch_timer_;
    float          launch_delay_ = 0;
    Direction      direction_ = Direction::Right;
    SoundEngine&   sound_engine_;
    std::mt19937&  rng_;

    int Rand(int min, int max);

   public:
    FireballUpdate(bool* is_paused, SoundEngine& sound_engine, std::mt19937& rng);
    Direction*     GetDirectionPointer();
    sf::FloatRect* GetPositionPointer();

    // From IUpdate : Component
    void Update(float elapsed_time) override;
    void Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) override;
};