#include "Platform.hpp"

bool Platform::isOffScreen(float viewLeft) const {
    return m_rect.position.x + m_rect.size.x < viewLeft;
}

void Platform::setRect(sf::FloatRect rect) {
    m_rect = rect;
}

sf::FloatRect Platform::getRect() const {
    return m_rect;
}