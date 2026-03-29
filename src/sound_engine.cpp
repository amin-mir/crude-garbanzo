#include "sound_engine.hpp"

#include <SFML/Audio/Listener.hpp>

SoundEngine::SoundEngine() {
    music_.openFromFile("sound/music.wav");
    click_buffer_.loadFromFile("sound/click.wav");
    click_sound_.setBuffer(click_buffer_);
    jump_buffer_.loadFromFile("sound/jump.wav");
    jump_sound_.setBuffer(jump_buffer_);

    sf::Listener::setDirection(1.f, 0.f, 0.f);
    sf::Listener::setUpVector(1.f, 1.f, 0.f);
    sf::Listener::setGlobalVolume(100.f);
    fireball_launch_buffer_.loadFromFile("sound/fireballLaunch.wav");
    fireball_launch_sound_.setBuffer(fireball_launch_buffer_);
}

void SoundEngine::PlayClick() {
    click_sound_.play();
}

void SoundEngine::PlayJump() {
    jump_sound_.play();
}

void SoundEngine::StartMusic() {
    music_.play();
    music_.setLoop(true);
}

void SoundEngine::PauseMusic() {
    music_.pause();
}

void SoundEngine::ResumeMusic() {
    music_.play();
}

void SoundEngine::StopMusic() {
    music_.stop();
}

bool SoundEngine::IsPlaying() {
    return music_.getStatus() == sf::SoundSource::Playing;
}

void SoundEngine::PlayFireballLaunch(sf::Vector2f player_pos, sf::Vector2f sound_loc) {
    float x_offset = (player_pos.x > sound_loc.x) ? -100.f : 100.f;

    // sf::Listener::setPosition(0, 0, 0.f);
    fireball_launch_sound_.setRelativeToListener(true);
    fireball_launch_sound_.setPosition(x_offset, 0, 0.f);
    fireball_launch_sound_.setMinDistance(100);
    fireball_launch_sound_.setAttenuation(0);
    fireball_launch_sound_.play();
}
