#include "camera_graphics.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "camera_update.hpp"

CameraGraphics::CameraGraphics(sf::RenderWindow* window, sf::Texture* texture, sf::Vector2f view_size,
                               sf::FloatRect viewport)
    : window_(window), texture_(texture) {
    view_.setSize(view_size);
    view_.setViewport(viewport);
    // The mini map viewport is less than 1
    if (viewport.width < 1) {
        is_mini_map_ = true;
    } else {
        // Only the full screen camera has the time text
        if (!font_.loadFromFile("fonts/KOMIKAP_.ttf")) {
            std::cout << "Font not loaded";
            return;
        }
        text_.setFont(font_);
        text_.setFillColor(sf::Color(255, 0, 0, 255));
        text_.setScale(0.2f, 0.2f);
    }

    bg_texture_.loadFromFile("graphics/backgroundTexture.png");
    bg1_.setTexture(bg_texture_);
    bg2_.setTexture(bg_texture_);
    bg1_.setPosition(0, -200);
    bg2_.setPosition(bg_texture_.getSize().x, -200);
}

void CameraGraphics::Assemble(sf::VertexArray& canvas, std::shared_ptr<IUpdate> update, sf::IntRect tex_coords) {
    auto camera_update = std::static_pointer_cast<CameraUpdate>(update);
    position_ = camera_update->GetPositionPointer();
    vertex_start_index_ = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

    const sf::Vector2f tex_pos(tex_coords.left, tex_coords.top);
    const sf::Vector2f tex_size(tex_coords.width, tex_coords.height);
    canvas[vertex_start_index_].texCoords = tex_pos;
    canvas[vertex_start_index_ + 1].texCoords = tex_pos + sf::Vector2f(tex_size.x, 0);
    canvas[vertex_start_index_ + 2].texCoords = tex_pos + tex_size;
    canvas[vertex_start_index_ + 3].texCoords = tex_pos + sf::Vector2f(0, tex_size.y);
}

float* CameraGraphics::GetTimeConnection() {
    return &time_;
}

void CameraGraphics::Draw(sf::VertexArray& canvas) {
    view_.setCenter(position_->getPosition());
    const sf::Vector2f start_pos(view_.getCenter().x - view_.getSize().x / 2,
                                 view_.getCenter().y - view_.getSize().y / 2);
    const sf::Vector2f scale = view_.getSize();
    canvas[vertex_start_index_].position = start_pos;
    canvas[vertex_start_index_ + 1].position = start_pos + sf::Vector2f(scale.x, 0);
    canvas[vertex_start_index_ + 2].position = start_pos + scale;
    canvas[vertex_start_index_ + 3].position = start_pos + sf::Vector2f(0, scale.y);
    if (is_mini_map_) {
        if (view_.getSize().x < kMaxWidth && position_->width > 1) {
            view_.zoom(position_->width);
        } else if (view_.getSize().x > kMinWidth && position_->width < 1) {
            view_.zoom(position_->width);
        }
    }
    window_->setView(view_);

    const sf::Vector2f movement(position_->left - prev_pos_.x, position_->top - prev_pos_.y);
    if (bg_flipped_) {
        bg2_.setPosition(bg2_.getPosition().x + movement.x / 6, bg2_.getPosition().y + movement.y / 6);
        bg1_.setPosition(bg2_.getPosition().x + bg2_.getTextureRect().getSize().x, bg2_.getPosition().y);
        if (position_->left > bg1_.getPosition().x + (bg1_.getTextureRect().getSize().x / 2)) {
            bg_flipped_ = !bg_flipped_;
            bg2_.setPosition(bg1_.getPosition());
        }
    } else {
        bg1_.setPosition(bg1_.getPosition().x - movement.x / 6, bg1_.getPosition().y + movement.y / 6);
        bg2_.setPosition(bg1_.getPosition().x + bg1_.getTextureRect().getSize().x, bg1_.getPosition().y);
        if (position_->left > bg2_.getPosition().x + (bg2_.getTextureRect().getSize().x / 2)) {
            bg_flipped_ = !bg_flipped_;
            bg1_.setPosition(bg2_.getPosition());
        }
    }
    prev_pos_ = position_->getPosition();

    window_->draw(bg1_);
    window_->draw(bg2_);

    // Draw the time UI but only in the main camera
    if (!is_mini_map_) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << time_;
        text_.setString(oss.str());
        text_.setPosition(window_->mapPixelToCoords(sf::Vector2i(5, 5)));
        window_->draw(text_);
    }
    // Draw the main canvas
    window_->draw(canvas, texture_);
}
