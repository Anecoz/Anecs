#include "Engine.h"

#include "Component.h"
#include "Entity.h"

namespace Anecs {

  Engine::Engine()
  {}

  Engine::~Engine()
  {}

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

  void Engine::addEntityNoSort(std::shared_ptr<Entity> entity)
  {
    _entities.push_back(entity);
  }
}