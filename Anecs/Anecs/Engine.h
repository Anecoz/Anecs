#pragma once

#include "ComponentUtils.h"

#include <vector>
#include <memory>
#include <unordered_map>

namespace Anecs {
  class Component;
  class Entity;

  /*
  Handles entities, systems and components
  */
  class Engine
  {
  public:
    typedef std::shared_ptr<std::vector<std::shared_ptr<Entity>>> EntityContainer;

    Engine();
    ~Engine();

    void addEntity(std::shared_ptr<Entity> entity);

    template <typename T>
    Engine::EntityContainer getEntitesWithComponent() const;

  private:
    std::vector<std::shared_ptr<Entity>> _entities;

    std::unordered_map<ComponentID, EntityContainer> _sortedEntities;
  };

  template <typename T>
  Engine::EntityContainer Engine::getEntitesWithComponent() const
  {
    auto id = ComponentUtils::getUniqueId<T>();
    if (_sortedEntities.find(id) == _sortedEntities.end())
    {
      return EntityContainer(new std::vector<std::shared_ptr<Entity>>());
    }
    return _sortedEntities.at(id);
  }
}


