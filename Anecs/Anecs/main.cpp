#include <iostream>
#include <chrono>

#include "Engine.h"
#include "Component.h"
#include "System.h"
#include "Entity.h"

class TestComp : public Anecs::Component
{
public:
  TestComp(int data) : Anecs::Component()
    , _data(data)
  {}

  int _data;
};

class TestSystem : public Anecs::System
{
public:
  TestSystem() : Anecs::System()
  {}

  void update(const Anecs::Engine& engine) override
  {
    auto entities = engine.getEntitesWithComponent<TestComp>();

    for (auto entity : *entities) {
      auto test = entity->getComponent<TestComp>();
      TestComp* testcomp = dynamic_cast<TestComp*>(test.get());
    }
  }
};

// Left todo:
/*
Need a System class
Need some sort of internal loop in engine to call systems etc
*/
int main()
{
  // Test getting entities with certain component
  Anecs::Engine engine;
  auto t1Add = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 100000; i++) {
    auto entity = std::make_unique<Anecs::Entity>();
    entity->addComponent<TestComp>(i);
    engine.addEntity(std::move(entity));
  }
  auto t2Add = std::chrono::high_resolution_clock::now();
  auto durationAdd = std::chrono::duration_cast<std::chrono::microseconds>(t2Add - t1Add).count();

  std::cout << "Adding entities to engine took " << durationAdd << " microseconds" << std::endl;

  auto t1Scnd = std::chrono::high_resolution_clock::now();
  auto entitiesScnd = engine.getEntitesWithComponent<TestComp>();
  auto t2Scnd = std::chrono::high_resolution_clock::now();
  auto durationScnd = std::chrono::duration_cast<std::chrono::microseconds>(t2Scnd - t1Scnd).count();

  std::cout << "Entities with component TestComp are: " << entitiesScnd->size() << std::endl;
  std::cout << "Fetching entities with a specific component took: " << durationScnd << " microseconds" << std::endl;

  std::unique_ptr<Anecs::System> testSystem(new TestSystem);
  engine.addSystem(std::move(testSystem));
  engine.start();

  int i;
  std::cin >> i;
}

