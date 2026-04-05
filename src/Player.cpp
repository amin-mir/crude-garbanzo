#include "Player.hpp"

#include <SFML/Window.hpp>

Player::Player(const PlatformManager& platformManager) : m_platformManager(platformManager) {
}

void Player::update(float dt) {
    // Horizontal movement
    bool boosting       = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
    bool movingBackward = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    bool movingForward =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);

    m_velocity.x = 0.f;

    // In air + boosting
    if (!m_onGround && boosting)
        m_moveSpeed = std::max(m_moveSpeed - BoostMoveSpeedTransitionRate * dt, BoostMoveSpeed);

    // In air without boost m_moveSpeed remains unchanged.
    if (!m_onGround && movingForward)
        m_velocity.x = m_moveSpeed;
    else if (movingForward)
        m_velocity.x = MoveSpeed;

    // In air without boost m_moveSpeed remains unchanged.
    if (!m_onGround && movingBackward)
        m_velocity.x = -m_moveSpeed;
    else if (movingBackward)
        m_velocity.x = -MoveSpeed;

    // Boost
    if (boosting && m_velocity.y > MaxRiseSpeed)
        m_velocity.y -= BoostForce * dt;

    // Gravity
    m_velocity.y += Gravity * dt;

    // Horizontal move + collision
    m_rect.position.x += m_velocity.x * dt;
    for (const auto& platform : m_platformManager.getPlatforms()) {
        if (auto intersection = m_rect.findIntersection(platform.getRect())) {
            auto platformRect = platform.getRect();
            if (m_velocity.x > 0.f)
                m_rect.position.x = platformRect.position.x - m_rect.size.x;
            else if (m_velocity.x < 0.f)
                m_rect.position.x = platformRect.position.x + platformRect.size.x;
            m_velocity.x = 0.f;
        }
    }

    // Vertical move + collision
    m_rect.position.y += m_velocity.y * dt;
    m_rect.position.y = std::max(m_rect.position.y, MinPlayerY);
    m_onGround        = false;
    for (const auto& platform : m_platformManager.getPlatforms()) {
        if (auto intersection = m_rect.findIntersection(platform.getRect())) {
            auto platformRect = platform.getRect();
            if (m_velocity.y > 0.f) {
                m_rect.position.y = platformRect.position.y - m_rect.size.y;
                m_onGround        = true;
                m_moveSpeed       = MoveSpeed;
            } else if (m_velocity.y < 0.f) {
                m_rect.position.y = platformRect.position.y + platformRect.size.y;
            }
            m_velocity.y = 0.f;
        }
    }

    // Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && m_onGround)
        m_velocity.y = -JumpSpeed;
}

sf::FloatRect Player::getRect() const {
    return m_rect;
}

sf::Vector2f Player::getVelocity() const {
    return m_velocity;
}
