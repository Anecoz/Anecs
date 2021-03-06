#pragma once

#include "ComponentUtils.h"

#include <atomic>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Anecs {
  class Component;
  class Entity;
  class System;

  /*
  Handles entities, systems and components
  */
  class Engine
  {
  public:
    typedef std::vector<std::shared_ptr<Entity>> EntityContainer;

    Engine();
    ~Engine();

    void start();
    void stop();

    void addEntity(std::unique_ptr<Entity> entity);
    void addSystem(std::unique_ptr<System> system, int priority = 0);

    template <typename T>
    std::shared_ptr<Engine::EntityContainer> getEntitesWithComponent() const;

  private:
    struct PrioritizedSystem
    {
      PrioritizedSystem(int priority, std::unique_ptr<System>&& system)
        : _priority(priority)
        , _system(std::move(system))
      {}

      int _priority;
      std::unique_ptr<System> _system;
    };

    bool _running;

    std::vector<PrioritizedSystem> _systems;
    std::unordered_map<ComponentID, std::shared_ptr<EntityContainer>> _sortedEntities;
  };

  template <typename T>
  std::shared_ptr<Engine::EntityContainer> Engine::getEntitesWithComponent() const
  {
    auto id = ComponentUtils::getUniqueId<T>();
    if (_sortedEntities.find(id) == _sortedEntities.end()) {
      return std::make_shared<EntityContainer>();
    }
    return _sortedEntities.at(id);
  }
}


