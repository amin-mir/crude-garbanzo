#pragma once

#include <SFML/Graphics.hpp>

class InputReceiver {
   public:
    void AddEvent(sf::Event event);
    std::vector<sf::Event>& GetEvents();
    void ClearEvents();

   private:
    std::vector<sf::Event> events_;
};
