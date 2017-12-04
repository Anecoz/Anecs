#pragma once

#include "Component.h"
#include "ComponentUtils.h"

#include <memory>
#include <array>
#include <bitset>
#include <vector>

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
    // Maybe add an overload which takes an existing shared_ptr component and adds it?
    
    template <class T>
    bool hasComponent() const;

    std::vector<ComponentID> getAttachedComponents();

  private:
    std::bitset<Component::MAX_COMPONENTS> _attachedComponents;
    std::array<std::unique_ptr<Component>, Component::MAX_COMPONENTS> _components;
  };

  template <class T, typename... Args>
  void Entity::addComponent(Args &&... args)
  {
    // TODO here: handle if we already have a component of this type, right now it simply gets overridden
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