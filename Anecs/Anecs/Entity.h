#pragma once

#include "Component.h"
#include "ComponentUtils.h"

#include <memory>
#include <array>
#include <bitset>

namespace Anecs {

  class Component;

  /*
  Represents any object in the system. The object itself is defined by the components attached to it.
  */
  class Entity
  {
  public:
    Entity();
    ~Entity();

    template <class T, typename... Args>
    void addComponent(Args &&... args);
    
    template <class T>
    bool hasComponent() const;

  private:
    std::bitset<Component::MAX_COMPONENTS> _attachedComponents;
    std::array<std::shared_ptr<Component>, Component::MAX_COMPONENTS> _components;
  };

  template <class T, typename... Args>
  void Entity::addComponent(Args &&... args)
  {
    static_assert(std::is_base_of<Component, T>::value, "Type T must inherit from Component!");
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    auto id = ComponentUtils::getUniqueId<T>();
    _components[id] = std::move(component);
    _attachedComponents[id] = true;
  }

  template <class T>
  bool Entity::hasComponent() const
  {
    auto id = ComponentUtils::getUniqueId<T>();
    return _attachedComponents[id];
  }
}