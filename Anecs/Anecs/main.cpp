#include <iostream>
#include <chrono>

#include "Engine.h"
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
  // Test getting entities with certain component
  Anecs::Engine engine;
  auto t1Add = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 100000; i++)
  {
    Anecs::Entity entity;
    entity.addComponent<TestComp>();
    engine.addEntity(std::shared_ptr<Anecs::Entity>(&entity));
  }
  auto t2Add = std::chrono::high_resolution_clock::now();
  auto durationAdd = std::chrono::duration_cast<std::chrono::microseconds>(t2Add - t1Add).count();

  std::cout << "Adding entities to engine took " << durationAdd << " microseconds" << std::endl;

  auto t1First = std::chrono::high_resolution_clock::now();
  auto entities = engine.getEntitesWithComponent1<TestComp>();
  auto t2First = std::chrono::high_resolution_clock::now();
  auto durationFirst = std::chrono::duration_cast<std::chrono::microseconds>(t2First - t1First).count();

  auto t1Scnd = std::chrono::high_resolution_clock::now();
  auto entitiesScnd = engine.getEntitesWithComponent2<TestComp>();
  auto t2Scnd = std::chrono::high_resolution_clock::now();
  auto durationScnd = std::chrono::duration_cast<std::chrono::microseconds>(t2Scnd - t1Scnd).count();

  std::cout << "Entities with component 1 TestComp are: " << entities.size() << std::endl;
  std::cout << "Entities with component 2 TestComp are: " << entitiesScnd->size() << std::endl;

  std::cout << "First solution took: " << durationFirst << " microseconds" << std::endl;
  std::cout << "Second solution took: " << durationScnd << " microseconds" << std::endl;

  // Sanity check
  auto entitiesEmpty = engine.getEntitesWithComponent2<TestComp2>();
  auto entitesEmpty2 = engine.getEntitesWithComponent1<TestComp2>();

  std::cout << "Entity lists that should be empty are: " << entitiesEmpty->size() << ", and: " << entitesEmpty2.size() << std::endl;

  int i;
  std::cin >> i;
}

