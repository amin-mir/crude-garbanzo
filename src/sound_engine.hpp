#pragma once

#include <SFML/Audio.hpp>

class SoundEngine {
   public:
    SoundEngine();
    bool IsPlaying();
    void StartMusic();
    void PauseMusic();
    void ResumeMusic();
    void StopMusic();
    void PlayClick();
    void PlayJump();
    void PlayFireballLaunch(sf::Vector2f player_pos, sf::Vector2f sound_loc);

   private:
    sf::Music       music_;
    sf::SoundBuffer click_buffer_;
    sf::Sound       click_sound_;
    sf::SoundBuffer jump_buffer_;
    sf::Sound       jump_sound_;
    sf::SoundBuffer fireball_launch_buffer_;
    sf::Sound       fireball_launch_sound_;
};
