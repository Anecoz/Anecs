#pragma once

#include <vector>
#include <memory>

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

    void addEntity(const std::shared_ptr<Entity> entity);

    template <typename T>
    std::vector<const std::shared_ptr<Entity>>& getEntitesWithComponent() const;

  private:
    std::vector<std::shared_ptr<Entity>> _entities;
  };

  template <typename T>
  std::vector<const std::shared_ptr<Entity>>& Engine::getEntitesWithComponent() const
  {

  }
}


