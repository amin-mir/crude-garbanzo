#pragma once

#include "input_receiver.hpp"

class InputDispatcher {
   public:
    InputDispatcher(sf::RenderWindow* window);
    void DispatchInputEvents();
    void RegisterNewInputReceiver(InputReceiver* ir);

   private:
    sf::RenderWindow* window_;
    std::vector<InputReceiver*> input_receivers_;
};
