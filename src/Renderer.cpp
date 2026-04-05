#include "Renderer.hpp"

#include <SFML/Graphics.hpp>

void Renderer::setQuad(sf::Vertex* tri, sf::Vector2f pos, sf::Vector2f size, sf::Vector2f texPos,
                       sf::Vector2f texSize) {
    tri[0] = {pos, sf::Color::White, texPos};
    tri[1] = {pos + sf::Vector2f(size.x, 0), sf::Color::White, texPos + sf::Vector2f(texSize.x, 0)};
    tri[2] = {pos + sf::Vector2f(0, size.y), sf::Color::White, texPos + sf::Vector2f(0, texSize.y)};
    tri[3] = {pos + sf::Vector2f(size.x, 0), sf::Color::White, texPos + sf::Vector2f(texSize.x, 0)};
    tri[4] = {pos + sf::Vector2f(size.x, size.y), sf::Color::White, texPos + texSize};
    tri[5] = {pos + sf::Vector2f(0, size.y), sf::Color::White, texPos + sf::Vector2f(0, texSize.y)};
}

Renderer::Renderer(const PlatformManager& platformManager, const Player& player)
    : m_platformManager(platformManager), m_player(player) {
    if (!m_texture.loadFromFile("graphics/texture.png"))
        throw std::runtime_error("could not load texture.png");

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize((NumPlatforms + 1) * 6);

    m_playerDebugRect.setFillColor(sf::Color::Transparent);
    m_playerDebugRect.setOutlineColor(sf::Color::Yellow);
    m_playerDebugRect.setOutlineThickness(1.f);
}

// Keep in mind for future design.
// void Renderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {}

void Renderer::draw(sf::RenderWindow& window) {
    const auto& platforms = m_platformManager.getPlatforms();
    for (size_t i = 0; i < platforms.size(); i++) {
        auto rect = platforms[i].getRect();
        setQuad(&m_vertices[i * 6], rect.position, rect.size, PlatformTexPos, PlatformTexSize);
    }

    auto rect = m_player.getRect();
    setQuad(&m_vertices[NumPlatforms * 6], rect.position, rect.size, PlayerTexPos, PlayerTexSize);

    window.draw(m_vertices, &m_texture);

    if (m_showPlayerDebugRect) {
        m_playerDebugRect.setPosition(rect.position);
        m_playerDebugRect.setSize(rect.size);
        window.draw(m_playerDebugRect);
    }
}

void Renderer::toggleDebugRects() {
    m_showPlayerDebugRect = !m_showPlayerDebugRect;
}
