#include "DebugOverlay.hpp"

#include <iterator>

DebugOverlay::DebugOverlay(sf::Vector2u screenSize, std::filesystem::path fontPath)
    : m_screenSize{screenSize}, m_font{fontPath}, m_text{m_font} {
    m_text.setCharacterSize(FontSize);
    m_border.setFillColor(sf::Color::Transparent);
    m_border.setOutlineColor(sf::Color::Yellow);
    m_border.setOutlineThickness(1.f);
}

void DebugOverlay::toggle() {
    m_visible = !m_visible;
}

void DebugOverlay::setPlayerInfo(sf::Vector2f pos, sf::Vector2f velocity) {
    m_playerPos      = pos;
    m_playerVelocity = velocity;
}

void DebugOverlay::update(sf::RenderWindow& window, int32_t elapsed) {
    if (!m_visible) {
        return;
    }

    m_elapsed += elapsed;
    if (m_elapsed > 50) {
        m_elapsed = 0;

        m_buf.clear();
        std::format_to(std::back_inserter(m_buf), "Player Pos({:.1f}, {:.1f})\nPlayer Vel({:.1f}, {:.1f})",
                       m_playerPos.x, m_playerPos.y, m_playerVelocity.x, m_playerVelocity.y);
        m_text.setString(m_buf);

        auto bounds = m_text.getLocalBounds();
        m_text.setPosition({m_screenSize.x - Padding - bounds.size.x, Padding});
        auto globalBounds = m_text.getGlobalBounds();
        m_border.setPosition(globalBounds.position);
        m_border.setSize(globalBounds.size);
    }
}

void DebugOverlay::draw(sf::RenderWindow& window) {
    if (!m_visible) {
        return;
    }
    window.draw(m_text);
    window.draw(m_border);
}
