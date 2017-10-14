#pragma once
#include <cstddef>

/*
Subclass this class and add to your entities to define their behaviour.
*/
namespace Anecs {

  class Component
  {
  public:
    static const std::size_t MAX_COMPONENTS = 64;

    Component() {}
    virtual ~Component() {}
  };
}