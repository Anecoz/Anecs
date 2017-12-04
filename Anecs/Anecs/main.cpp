#include <iostream>
#include "Component.h"
#include "Entity.h"

class TestComp : public Anecs::Component
{
public:
  TestComp() :
    Anecs::Component()
  {}
};

class TestComp2 : public Anecs::Component
{
public:
  TestComp2() :
    Anecs::Component()
  {}
};

// Entry point for testing
int main()
{
  Anecs::Entity entity;
  entity.addComponent<TestComp>();

  std::cout << "has component TestComp: " << entity.hasComponent<TestComp>() << std::endl;
  std::cout << "has component TestComp2: " << entity.hasComponent<TestComp2>() << std::endl;
  
  std::cout << "Adding a TestComp2 component..." << std::endl;
  entity.addComponent<TestComp2>();
  std::cout << "has component TestComp2: " << entity.hasComponent<TestComp2>() << std::endl;

  int i;
  std::cin >> i;
}

