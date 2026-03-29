#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

#include "factory.hpp"
#include "game_object.hpp"
#include "input_dispatcher.hpp"
#include "sound_engine.hpp"

using namespace std;
using namespace sf;

int main() {
    std::mt19937 rng(std::random_device{}());

    RenderWindow window(VideoMode::getDesktopMode(), "Booster", Style::Fullscreen);

    VertexArray        canvas(Quads, 0);
    InputDispatcher    input_dispatcher(&window);
    vector<GameObject> game_objects;
    SoundEngine        sound_engine;
    Factory            factory(&window, sound_engine, rng);
    factory.LoadLevel(game_objects, canvas, input_dispatcher);

    Clock clock;

    const Color kBackgroundColor(100, 100, 100, 255);

    while (window.isOpen()) {
        float elapsed_time = clock.restart().asSeconds();

        input_dispatcher.DispatchInputEvents();

        window.clear(kBackgroundColor);

        for (auto& gobj : game_objects) {
            gobj.Update(elapsed_time);
        }
        for (auto& gobj : game_objects) {
            gobj.Draw(canvas);
        }
        window.display();
    }

    return 0;
}
