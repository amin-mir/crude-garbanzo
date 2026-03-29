#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "component.hpp"

class GameObject {
   public:
    void AddComponent(std::shared_ptr<Component> new_component);
    void Update(float elapsed_time);
    void Draw(sf::VertexArray& canvas);

   private:
    std::vector<std::shared_ptr<Component>> components_;
};
