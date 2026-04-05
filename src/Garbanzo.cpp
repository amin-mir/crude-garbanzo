#include "Camera.hpp"
#include "DebugOverlay.hpp"
#include "PlatformManager.hpp"
#include "Player.hpp"
#include "Renderer.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <random>

constexpr sf::Vector2u ScreenSize({1280, 720});

int main() {
    sf::RenderWindow window(sf::VideoMode(ScreenSize), "Gorbanzo");

    std::mt19937 rng(std::random_device{}());
    sf::Clock    clock;

    DebugOverlay    debugOverlay(ScreenSize, "/System/Library/Fonts/Menlo.ttc");
    PlatformManager platformManager{rng};
    Player          player(platformManager);
    Renderer        renderer(platformManager, player);
    Camera          camera(ScreenSize, player);

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* kr = event->getIf<sf::Event::KeyReleased>()) {
                if (kr->scancode == sf::Keyboard::Scancode::D && kr->control) {
                    debugOverlay.toggle();
                    renderer.toggleDebugRects();
                }
            }
        }

        float elapsedSec = elapsed.asSeconds();
        player.update(elapsedSec);
        debugOverlay.setPlayerInfo(player.getRect().position, player.getVelocity());
        camera.update();
        platformManager.update(camera.getViewLeft());

        debugOverlay.update(window, elapsed.asMilliseconds());

        window.clear();
        window.setView(camera.getView());
        renderer.draw(window);
        window.setView(window.getDefaultView());
        debugOverlay.draw(window);
        window.display();
    }
}
