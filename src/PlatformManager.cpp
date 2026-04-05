#include "PlatformManager.hpp"

PlatformManager::PlatformManager(std::mt19937& rng) : m_rng{rng} {
    float x = 0.f;
    for (auto& p : m_platforms) {
        float w = m_widthDist(m_rng);
        float y = m_yDist(m_rng);
        p.setRect({{x, y}, {w, PlatformHeight}});
        x += w + m_gapDist(m_rng);
    }
}

const std::array<Platform, NumPlatforms>& PlatformManager::getPlatforms() const {
    return m_platforms;
}

void PlatformManager::update(float viewLeft) {
    recycle(viewLeft);
}

void PlatformManager::recycle(float viewLeft) {
    if (m_platforms[m_head].isOffScreen(viewLeft)) {
        auto  rightmost = m_platforms[(m_head - 1 + NumPlatforms) % NumPlatforms].getRect();
        float newX      = rightmost.position.x + rightmost.size.x + m_gapDist(m_rng);
        m_platforms[m_head].setRect({{newX, m_yDist(m_rng)}, {m_widthDist(m_rng), PlatformHeight}});
        m_head = (m_head + 1) % m_platforms.size();
    }
}