#pragma once

#include <SFML/Graphics.hpp>

#include <filesystem>

class DebugOverlay {
  public:
    DebugOverlay(sf::Vector2u screenSize, std::filesystem::path fontPath);

    void toggle();
    void setPlayerInfo(sf::Vector2f pos, sf::Vector2f velocity);
    void update(sf::RenderWindow& window, int32_t elapsed);
    void draw(sf::RenderWindow& window);

  private:
    static constexpr float Padding  = 10.f;
    static constexpr int   FontSize = 13;

    int32_t            m_elapsed{0};
    sf::Vector2f       m_playerPos;
    sf::Vector2f       m_playerVelocity;
    bool               m_visible{false};
    sf::Vector2u       m_screenSize;
    sf::Font           m_font;
    sf::Text           m_text;
    std::string        m_buf;
    sf::RectangleShape m_border;
};
