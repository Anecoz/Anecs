#include "Engine.h"

#include "Component.h"
#include "Entity.h"

namespace Anecs {

  Engine::Engine()
  {}

  Engine::~Engine()
  {}

  void Engine::addEntity(const std::shared_ptr<Entity> entity)
  {
    _entities.emplace_back(entity);
  }
}