#include "Engine.h"

#include "System.h"
#include "Component.h"
#include "Entity.h"

#include <algorithm>

namespace Anecs {

  Engine::Engine()
    : _running(false)
  {}

  Engine::~Engine()
  {}

  void Engine::start()
  {
    _running = true;

    while (_running) {
      for (auto& system : _systems) {
        system._system->update(*this);
      }
    }
  }

  void Engine::stop()
  {}

  void Engine::addEntity(std::unique_ptr<Entity> entity)
  {
    std::shared_ptr<Entity> shared = std::move(entity);

    for (auto& id : shared->getAttachedComponents()) {
      if (_sortedEntities.find(id) == _sortedEntities.end()) {
        _sortedEntities[id] = std::make_shared<EntityContainer>();
      }
      _sortedEntities[id]->push_back(shared);
    }
  }

  void Engine::addSystem(std::unique_ptr<System> system, int priority)
  {
    _systems.emplace_back(priority, std::move(system));

    std::sort(_systems.begin(), _systems.end(), [](const PrioritizedSystem& system1, const PrioritizedSystem& system2) {
      return system1._priority < system2._priority;
    });
  }
}