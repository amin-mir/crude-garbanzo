#pragma once

#include "Platform.hpp"

#include <array>
#include <random>

namespace {
constexpr size_t NumPlatforms = 10;
}

class PlatformManager {
  public:
    explicit PlatformManager(std::mt19937& rng);
    void                                      update(float viewLeft);
    const std::array<Platform, NumPlatforms>& getPlatforms() const;

  private:
    static constexpr float PlatformHeight = 18.f;

    std::mt19937&                         m_rng;
    std::array<Platform, NumPlatforms>    m_platforms;
    size_t                                m_head{0};
    std::uniform_real_distribution<float> m_widthDist{80.f, 220.f};
    std::uniform_real_distribution<float> m_yDist{300.f, 550.f};
    std::uniform_real_distribution<float> m_gapDist{80.f, 200.f};

    void recycle(float viewLeft);
};