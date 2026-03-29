#include "animator.hpp"

Animator::Animator(int left_offset, int top_offset, int frame_count, int texture_width, int texture_height, int fps) {
    left_offset_ = left_offset;
    current_frame_ = 0;
    frame_count_ = frame_count;
    frame_width_ = texture_width / frame_count_;
    source_rect_.left = left_offset;
    source_rect_.top = top_offset;
    source_rect_.width = frame_width_;
    source_rect_.height = texture_height;
    fps_ = fps;
    frame_period_ = 1000 / fps_;
    clock_.restart();
}

sf::IntRect* Animator::GetCurrentFrame(bool reversed) {
    // Reversed adds 1 to the frame number
    // when drawing the texture reversed.
    // This works because reversed
    // (flipped horizontally) textures
    // are drawn pixels right to left
    if (clock_.getElapsedTime().asMilliseconds() > frame_period_) {
        current_frame_++;
        if (current_frame_ >= frame_count_ + reversed) {
            current_frame_ = 0 + reversed;
        }
        clock_.restart();
    }
    source_rect_.left = left_offset_ + current_frame_ * frame_width_;
    return &source_rect_;
}
