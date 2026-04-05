#include "Player.hpp"

#include <SFML/Graphics.hpp>

class Camera {
  public:
    Camera(sf::Vector2u windowSize, const Player& player);
    void            update();
    float           getViewLeft() const;
    const sf::View& getView() const;

  private:
    const Player& m_player;
    sf::View      m_view;
};