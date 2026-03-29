#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

#include "game_object.hpp"
#include "input_dispatcher.hpp"
#include "sound_engine.hpp"

class Factory {
   public:
    Factory(sf::RenderWindow* window, SoundEngine& se, std::mt19937& rng);

    sf::Texture* texture_;

    void LoadLevel(std::vector<GameObject>& game_objects, sf::VertexArray& canvas, InputDispatcher& input_dispatcher);

   private:
    static constexpr int   kPlayerTexLeft = 0;
    static constexpr int   kPlayerTexTop = 0;
    static constexpr int   kPlayerTexWidth = 80;
    static constexpr int   kPlayerTexHeight = 96;
    static constexpr float kCamViewWidth = 300.f;
    static constexpr float kCamScreenRatioLeft = 0.f;
    static constexpr float kCamScreenRatioTop = 0.f;
    static constexpr float kCamScreenRatioWidth = 1.f;
    static constexpr float kCamScreenRatioHeight = 1.f;
    static constexpr int   kCamTexLeft = 610;
    static constexpr int   kCamTexTop = 36;
    static constexpr int   kCamTexWidth = 40;
    static constexpr int   kCamTexHeight = 30;
    static constexpr float kMapCamScreenRatioLeft = 0.3f;
    static constexpr float kMapCamScreenRatioTop = 0.84f;
    static constexpr float kMapCamScreenRatioWidth = 0.4f;
    static constexpr float kMapCamScreenRatioHeight = 0.15f;
    static constexpr float kMapCamViewWidth = 800.f;
    static constexpr float kMapCamViewHeight = kMapCamViewWidth / 2;
    static constexpr int   kMapCamTexLeft = 665;
    static constexpr int   kMapCamTexTop = 0;
    static constexpr int   kMapCamTexWidth = 100;
    static constexpr int   kMapCamTexHeight = 70;
    static constexpr int   kPlatformTexLeft = 607;
    static constexpr int   kPlatformTexTop = 0;
    static constexpr int   kPlatformTexWidth = 10;
    static constexpr int   kPlatformTexHeight = 10;
    static constexpr int   kTopMenuTexLeft = 770;
    static constexpr int   kTopMenuTexTop = 0;
    static constexpr int   kTopMenuTexWidth = 100;
    static constexpr int   kTopMenuTexHeight = 100;
    static constexpr int   kRainTexLeft = 0;
    static constexpr int   kRainTexTop = 100;
    static constexpr int   kRainTexWidth = 100;
    static constexpr int   kRainTexHeight = 100;

    sf::RenderWindow* window_;
    SoundEngine&      sound_engine_;
    std::mt19937&     rng_;
};
