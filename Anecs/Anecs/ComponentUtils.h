#pragma once
#include <cstddef>

namespace Anecs
{
  /*
  Utilities for aid in using components.
  */

  typedef std::size_t ComponentID;

  class ComponentUtils
  {
  public:
    ComponentUtils() = delete;
    ~ComponentUtils() = delete;
    /*
    Helper function to get a unique ID for a certain component type.
    */
    template <class T>
    static ComponentID getUniqueId()
    {
      static_assert(std::is_base_of<Component, T>::value, "Type T must inherit from Component!");
      static ComponentID typeID = internalGetId();
      return typeID;
    }

  private:
    static ComponentID internalGetId()
    {
      static ComponentID id(0);
      return id++;
    }
  };
}