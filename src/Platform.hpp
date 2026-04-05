#pragma once

#include <SFML/Graphics.hpp>

class Platform {
  public:
    bool          isOffScreen(float viewLeft) const;
    void          setRect(sf::FloatRect rect);
    sf::FloatRect getRect() const;

  private:
    sf::FloatRect m_rect;
};