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

    auto attached = entity->getAttachedComponents();

    for (auto& id : attached)
    {
      if (_sortedEntities.find(id) == _sortedEntities.end())
      {
        _sortedEntities[id] = new std::vector<std::shared_ptr<Entity>>();
      }

      _sortedEntities[id]->push_back(entity);   
    }
  }

  void Engine::addEntityNoSort(std::shared_ptr<Entity> entity)
  {
    _entities.push_back(entity);
  }
}