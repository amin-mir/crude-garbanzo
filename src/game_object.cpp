#include "game_object.hpp"

#include <iostream>

void GameObject::AddComponent(std::shared_ptr<Component> new_component) { components_.push_back(new_component); }

void GameObject::Update(float elapsed_time) {
    // Without the const auto& we would be copying the shared_ptr in every loop iteration which
    // increments and decrements the reference count. We can still call non-constant methods on 
    // the pointed-to object because const applies to shared_ptr not to the pointee.
    for (const auto& component : components_) {
        component->Update(elapsed_time);
    }
}

void GameObject::Draw(sf::VertexArray& canvas) {
    for (const auto& component : components_) {
        component->Draw(canvas);
    }
}
