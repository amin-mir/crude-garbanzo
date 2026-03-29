#pragma once

#include <memory>

#include "component.hpp"

// Forward declaration.
class LevelUpdate;
class PlayerUpdate;

class IUpdate : public Component {
   public:
    virtual void Assemble(std::shared_ptr<LevelUpdate> level_update, std::shared_ptr<PlayerUpdate> player_update) = 0;
    virtual void Update(float elapsed_time) = 0;
};
