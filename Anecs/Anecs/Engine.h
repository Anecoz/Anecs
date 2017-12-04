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
    Engine();
    ~Engine();

    void addEntity(std::shared_ptr<Entity> entity);
    void addEntityNoSort(std::shared_ptr<Entity> entity);

    template <typename T>
    std::vector<std::shared_ptr<Entity>> getEntitesWithComponent1() const;
    template <typename T>
    std::vector<std::shared_ptr<Entity>>* getEntitesWithComponent2() const;

  private:
    std::vector<std::shared_ptr<Entity>> _entities;
    std::unordered_map<ComponentID, std::vector<std::shared_ptr<Entity>>*> _sortedEntities;
  };

  template <typename T>
  std::vector<std::shared_ptr<Entity>> Engine::getEntitesWithComponent1() const
  {
    // FIRST SOLUTION
    std::vector<std::shared_ptr<Entity>> output;
    for (auto entity : _entities)
    {
      if (entity->hasComponent<T>()) output.push_back(entity);
    }
    return output;
  }

  template <typename T>
  std::vector<std::shared_ptr<Entity>>* Engine::getEntitesWithComponent2() const
  {
    // SECOND SOLUTION
    auto id = ComponentUtils::getUniqueId<T>();
    if (_sortedEntities.find(id) == _sortedEntities.end()) return new std::vector<std::shared_ptr<Entity>>();
    return _sortedEntities.at(id);
  }
}


