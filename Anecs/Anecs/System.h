#pragma once

namespace Anecs
{
class Engine;

class System
{
public:
  System() {}
  virtual ~System() {}

  virtual void update(const Anecs::Engine& engine) = 0;
};
}