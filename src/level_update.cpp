#include "level_update.hpp"

#include <algorithm>
#include <ranges>

#include "player_update.hpp"

LevelUpdate::LevelUpdate(SoundEngine& se, std::mt19937& rng) : sound_engine_{se}, rng_{rng} {}

void LevelUpdate::ConnectToCameraTime(float* ct) { camera_time_ = ct; }

void LevelUpdate::AddPlatformPosition(sf::FloatRect* pos) { platforms_.push_back(pos); }

// TODO: why return a ptr?
bool* LevelUpdate::GetIsPausedPointer() { return &is_paused_; }

void LevelUpdate::PositionLevelAtStart() {
    float start_offset = platforms_[0]->left;
    for (auto [i, pos] : std::views::enumerate(platforms_)) {
        pos->left = i * 100 + start_offset;
        pos->top = 0;
        pos->width = 100;
        pos->height = 20;
    }

    player_position_->left = platforms_[platforms_.size() / 2]->left + 2;
    player_position_->top = platforms_[platforms_.size() / 2]->top - 22;
    last_placed_idx_ = platforms_.size() - 1;
    recycle_idx_ = 0;
}

void LevelUpdate::Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) {
    // TODO: if we're getting a shared_ptr, why not use that instead of acquiring a pointer to
    // a field inside it?
    player_position_ = player_update->GetPositionPointer();
    sound_engine_.StartMusic();
}

void LevelUpdate::Update(float elapsed_time) {
    if (is_paused_) return;

    if (game_over_) {
        game_over_ = false;
        *camera_time_ = 0;
        time_since_last_platform_ = 0;
        PositionLevelAtStart();
    }

    *camera_time_ += elapsed_time;
    time_since_last_platform_ += elapsed_time;
    if (time_since_last_platform_ > platform_creation_interval_) RecycleNextPlatform();

    if (PlayerIsLaggingBehind()) {
        is_paused_ = true;
        game_over_ = true;
        sound_engine_.PauseMusic();
    }
}

void LevelUpdate::RecycleNextPlatform() {
    sf::FloatRect*       next = platforms_[recycle_idx_];
    const sf::FloatRect* anchor = platforms_[last_placed_idx_];

    next->top = anchor->top + Rand(-40, 40);

    bool dropping = next->top > anchor->top;
    next->left = anchor->left + anchor->width + (dropping ? Rand(20, 40) : Rand(0, 20));

    next->width = Rand(20, 200);
    next->height = Rand(10, 20);

    platform_creation_interval_ = next->width / 110.f;
    last_placed_idx_ = recycle_idx_;
    recycle_idx_ = (recycle_idx_ + 1) % static_cast<int>(platforms_.size());
    time_since_last_platform_ = 0;
}

bool LevelUpdate::PlayerIsLaggingBehind() const {
    return std::ranges::all_of(platforms_, [&](auto pos) { return pos->left > player_position_->left; });
}

int LevelUpdate::Rand(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng_);
}
