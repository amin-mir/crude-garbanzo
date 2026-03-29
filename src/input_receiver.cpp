#include "input_receiver.hpp"

void InputReceiver::AddEvent(sf::Event event) { events_.push_back(event); }

std::vector<sf::Event>& InputReceiver::GetEvents() { return events_; }

void InputReceiver::ClearEvents() { events_.clear(); }
