#include "factory.hpp"

#include <iostream>

#include "camera_graphics.hpp"
#include "camera_update.hpp"
#include "fireball_graphics.hpp"
#include "fireball_update.hpp"
#include "input_dispatcher.hpp"
#include "level_update.hpp"
#include "menu_graphics.hpp"
#include "menu_update.hpp"
#include "platform_graphics.hpp"
#include "platform_update.hpp"
#include "player_graphics.hpp"
#include "player_update.hpp"
#include "rain_graphics.hpp"

Factory::Factory(sf::RenderWindow* window, SoundEngine& se, std::mt19937& rng) : sound_engine_{se}, rng_{rng} {
    window_ = window;
    // TODO: do we need heap allocation here?
    texture_ = new sf::Texture();
    if (!texture_->loadFromFile("graphics/texture.png")) {
        std::cout << "Texture not loaded";
        return;
    }
}

void Factory::LoadLevel(std::vector<GameObject>& game_objects, sf::VertexArray& canvas,
                        InputDispatcher& input_dispatcher) {
    GameObject                   level;
    std::shared_ptr<LevelUpdate> level_update = std::make_shared<LevelUpdate>(sound_engine_, rng_);
    level.AddComponent(level_update);
    game_objects.push_back(level);

    // Player
    GameObject                    player;
    std::shared_ptr<PlayerUpdate> player_update = std::make_shared<PlayerUpdate>(sound_engine_);
    player_update->Assemble(level_update, nullptr);
    player.AddComponent(player_update);
    input_dispatcher.RegisterNewInputReceiver(player_update->GetInputReceiver());

    std::shared_ptr<PlayerGraphics> player_graphics = std::make_shared<PlayerGraphics>();
    auto player_coords = sf::IntRect(kPlayerTexLeft, kPlayerTexTop, kPlayerTexWidth, kPlayerTexHeight);
    player_graphics->Assemble(canvas, player_update, player_coords);
    player.AddComponent(player_graphics);
    game_objects.push_back(player);

    level_update->Assemble(nullptr, player_update);

    // Platform
    for (int i = 0; i < 12; ++i) {
        GameObject platform;
        auto       platform_update = std::make_shared<PlatformUpdate>();
        platform_update->Assemble(nullptr, player_update);
        platform.AddComponent(platform_update);
        auto platform_graphics = std::make_shared<PlatformGraphics>();
        auto platform_coords = sf::IntRect(kPlatformTexLeft, kPlatformTexTop, kPlatformTexWidth, kPlatformTexHeight);
        platform_graphics->Assemble(canvas, platform_update, platform_coords);
        platform.AddComponent(platform_graphics);
        game_objects.push_back(platform);
        level_update->AddPlatformPosition(platform_update->GetPositionPointer());
    }

    for (int i = 0; i < 12; ++i) {
        GameObject fireball;
        auto       fireball_update =
            std::make_shared<FireballUpdate>(level_update->GetIsPausedPointer(), sound_engine_, rng_);
        fireball_update->Assemble(level_update, player_update);
        fireball.AddComponent(fireball_update);
        auto fireball_graphics = std::make_shared<FireballGraphics>();
        auto fireball_coords = sf::IntRect(870, 0, 32, 32);
        fireball_graphics->Assemble(canvas, fireball_update, fireball_coords);
        fireball.AddComponent(fireball_graphics);
        game_objects.push_back(fireball);
    }

    // Rain
    const int rain_coverage_per_object = 25;
    const int area_to_cover = 350;
    for (int h = -area_to_cover / 2; h < area_to_cover / 2; h += rain_coverage_per_object) {
        for (int v = -area_to_cover / 2; v < area_to_cover / 2; v += rain_coverage_per_object) {
            GameObject rain;
            auto       rain_coords = sf::IntRect(kRainTexLeft, kRainTexTop, kRainTexWidth, kRainTexHeight);
            auto       rain_graphics =
                std::make_shared<RainGraphics>(player_update->GetPositionPointer(), h, v, rain_coverage_per_object);
            rain_graphics->Assemble(canvas, nullptr, rain_coords);
            rain.AddComponent(rain_graphics);
            game_objects.push_back(rain);
        }
    }

    // Camera
    const float width = static_cast<float>(sf::VideoMode::getDesktopMode().width);
    const float height = static_cast<float>(sf::VideoMode::getDesktopMode().height);
    const float ratio = width / height;

    GameObject camera;
    auto       camera_update = std::make_shared<CameraUpdate>();
    camera_update->Assemble(nullptr, player_update);
    camera.AddComponent(camera_update);
    auto cam_view_size = sf::Vector2f(kCamViewWidth, kCamViewWidth / ratio);
    auto cam_viewport =
        sf::FloatRect(kCamScreenRatioLeft, kCamScreenRatioTop, kCamScreenRatioWidth, kCamScreenRatioHeight);
    auto camera_graphics = std::make_shared<CameraGraphics>(window_, texture_, cam_view_size, cam_viewport);
    auto cam_coords = sf::IntRect(kCamTexLeft, kCamTexTop, kCamTexWidth, kCamTexHeight);
    camera_graphics->Assemble(canvas, camera_update, cam_coords);
    camera.AddComponent(camera_graphics);
    game_objects.push_back(camera);
    level_update->ConnectToCameraTime(camera_graphics->GetTimeConnection());

    GameObject map_camera;
    auto       map_camera_update = std::make_shared<CameraUpdate>();
    map_camera_update->Assemble(nullptr, player_update);
    map_camera.AddComponent(map_camera_update);
    input_dispatcher.RegisterNewInputReceiver(map_camera_update->GetInputReceiver());
    auto map_cam_view_size = sf::Vector2f(kMapCamViewWidth, kMapCamViewHeight / ratio);
    auto map_cam_viewport =
        sf::FloatRect(kMapCamScreenRatioLeft, kMapCamScreenRatioTop, kMapCamScreenRatioWidth, kMapCamScreenRatioHeight);
    auto map_camera_graphics = std::make_shared<CameraGraphics>(window_, texture_, map_cam_view_size, map_cam_viewport);
    auto map_cam_coords = sf::IntRect(kMapCamTexLeft, kMapCamTexTop, kMapCamTexWidth, kMapCamTexHeight);
    map_camera_graphics->Assemble(canvas, map_camera_update, map_cam_coords);
    map_camera.AddComponent(map_camera_graphics);
    game_objects.push_back(map_camera);

    // Menu
    GameObject menu;
    auto       menu_update = std::make_shared<MenuUpdate>(window_, sound_engine_);
    menu_update->Assemble(level_update, player_update);
    input_dispatcher.RegisterNewInputReceiver(menu_update->GetInputReceiver());
    menu.AddComponent(menu_update);
    auto menu_graphics = std::make_shared<MenuGraphics>();
    auto menu_coords = sf::IntRect(kTopMenuTexLeft, kTopMenuTexTop, kTopMenuTexWidth, kTopMenuTexHeight);
    menu_graphics->Assemble(canvas, menu_update, menu_coords);
    menu.AddComponent(menu_graphics);
    game_objects.push_back(menu);
}
