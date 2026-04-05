#include "PlatformManager.hpp"
#include "Player.hpp"

#include <SFML/Graphics.hpp>

class Renderer {
  public:
    Renderer(const PlatformManager& platformManager, const Player& player);
    void draw(sf::RenderWindow& window);
    void toggleDebugRects();

  private:
    static constexpr size_t       NumPlatforms = 10;
    static constexpr sf::Vector2f PlatformTexPos{607, 0};
    static constexpr sf::Vector2f PlatformTexSize{10, 10};
    static constexpr sf::Vector2f PlayerTexPos{0, 0};
    static constexpr sf::Vector2f PlayerTexSize{65, 95};

    static void setQuad(sf::Vertex* tri, sf::Vector2f pos, sf::Vector2f size, sf::Vector2f texPos,
                        sf::Vector2f texSize);

    const PlatformManager& m_platformManager;
    const Player&          m_player;
    sf::RectangleShape     m_playerDebugRect;
    bool                   m_showPlayerDebugRect = false;
    sf::Texture            m_texture;
    sf::VertexArray        m_vertices;
};
