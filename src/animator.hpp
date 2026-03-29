#pragma once

#include <SFML/Graphics.hpp>

class Animator {
   public:
    Animator(int left_offset, int top_offset, int frame_count, int texture_width, int texture_height, int fps);
    sf::IntRect* GetCurrentFrame(bool reversed);

   private:
    sf::IntRect source_rect_;
    int         left_offset_;
    int         frame_count_;
    int         current_frame_;
    int         frame_period_;
    int         frame_width_;
    int         fps_ = 12;
    sf::Clock   clock_;
};
