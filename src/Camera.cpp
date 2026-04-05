#include "Camera.hpp"

Camera::Camera(sf::Vector2u windowSize, const Player& player)
    : m_player(player), m_view(sf::FloatRect({0.f, 0.f}, sf::Vector2f(windowSize))) {}

const sf::View& Camera::getView() const {
    return m_view;
}

float Camera::getViewLeft() const {
    return m_view.getCenter().x - m_view.getSize().x / 2.f;
}

void Camera::update() {
    auto playerCenter = m_player.getRect().getCenter();
    m_view.setCenter({playerCenter.x + m_view.getSize().x * 0.25f, m_view.getCenter().y});
}
