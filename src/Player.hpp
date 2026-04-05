#pragma once

#include "PlatformManager.hpp"

#include <SFML/Graphics.hpp>

class Player {
  public:
    Player(const PlatformManager& platformManager);
    void          update(float dt);
    sf::FloatRect getRect() const;
    sf::Vector2f  getVelocity() const;

  private:
    static constexpr float Gravity                      = 1200.f;
    static constexpr float JumpSpeed                    = 600.f;
    static constexpr float BoostForce                   = 2000.f;
    static constexpr float MoveSpeed                    = 300.f;
    static constexpr float PlayerWidth                  = 80.f;
    static constexpr float PlayerHeight                 = 120.f;
    static constexpr float MinPlayerY                   = 50.f;
    static constexpr float MaxRiseSpeed                 = -300.f;
    static constexpr float MaxFallSpeed                 = 450.f;
    static constexpr float BoostMoveSpeed               = 100.f;
    static constexpr float BoostMoveSpeedTransitionRate = 300.f;

    const PlatformManager& m_platformManager;
    sf::FloatRect          m_rect{{0.f, 300.f}, {PlayerWidth, PlayerHeight}};
    sf::Vector2f           m_velocity{0.f, 0.f};
    bool                   m_onGround{false};
    float                  m_moveSpeed = MoveSpeed;
};
