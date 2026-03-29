#pragma once

#include <random>

#include "sound_engine.hpp"
#include "update.hpp"

class LevelUpdate : public IUpdate {
   public:
    LevelUpdate(SoundEngine& sound_engine, std::mt19937& rng);
    void  AddPlatformPosition(sf::FloatRect* new_position);
    void  ConnectToCameraTime(float* camera_time);
    bool* GetIsPausedPointer();

    // From IUpdate : Component
    void Update(float fps) override;
    void Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) override;

   private:
    bool                        is_paused_ = true;
    std::vector<sf::FloatRect*> platforms_;
    // TODO: do we need a heap allocation here?
    float*         camera_time_ = new float;
    sf::FloatRect* player_position_;
    float          platform_creation_interval_ = 0;
    float          time_since_last_platform_ = 0;
    int            recycle_idx_ = 0;
    int            last_placed_idx_ = 0;
    bool           game_over_ = true;
    SoundEngine&   sound_engine_;
    std::mt19937&  rng_;

    void PositionLevelAtStart();
    void RecycleNextPlatform();
    bool PlayerIsLaggingBehind() const;
    int  Rand(int min_height, int max_height);
};
