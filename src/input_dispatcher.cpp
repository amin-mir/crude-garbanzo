#include "input_dispatcher.hpp"

InputDispatcher::InputDispatcher(sf::RenderWindow* window) { window_ = window; }

void InputDispatcher::DispatchInputEvents() {
    sf::Event event;
    while (window_->pollEvent(event)) {
        // Avoids copying the pointer.
        // Avoids pointer reassignment.
        for (const auto& ir : input_receivers_) {
            ir->AddEvent(event);
        }
    }
}

void InputDispatcher::RegisterNewInputReceiver(InputReceiver* ir) { input_receivers_.push_back(ir); }
