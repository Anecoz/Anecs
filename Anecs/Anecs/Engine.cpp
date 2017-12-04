#include "Engine.h"

#include "System.h"
#include "Component.h"
#include "Entity.h"

namespace Anecs {

  Engine::Engine()
    : _running(false)
  {}

  Engine::~Engine()
  {}

  void Engine::start()
  {
    _running = true;

    while (_running)
    {
      for (auto& system : _systems)
      {
        system->update(*this);
      }
    }
  }

  void Engine::stop()
  {

  }

  void Engine::addEntity(std::shared_ptr<Entity> entity)
  {
    _entities.push_back(entity);

    for (auto& id : entity->getAttachedComponents())
    {
      if (_sortedEntities.find(id) == _sortedEntities.end())
      {
        _sortedEntities[id] = EntityContainer(new std::vector<std::shared_ptr<Entity>>());
      }
      _sortedEntities[id]->push_back(entity);
    }
  }

  void Engine::addSystem(std::unique_ptr<System> system)
  {
    _systems.push_back(std::move(system));
  }
}