#include "Entity.h"

#include <array>
#include <bitset>

namespace Anecs {

  Entity::Entity()
  {
  }

  Entity::~Entity()
  {
  }

  std::vector<ComponentID> Entity::getAttachedComponents()
  {
    std::vector<ComponentID> output;

    ComponentID idx = 0;
    while (idx < _attachedComponents.size()) {
      if (_attachedComponents.test(idx)) {
        output.push_back(idx);
      }
      idx++;
    }

    return output;
  }
}