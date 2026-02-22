#pragma once
#include <string>
#include <iostream>
#include "GameObject.h"

class Goblin : public GameObject {
 public:
  Goblin(const std::string& name, float x, float y)
    : Name(name), xPosition(x), yPosition(y) {}

  void Tick(float TimeDelta) override {
    xPosition += Velocity * TimeDelta;
    std::cout << "Goblin position: "
      << xPosition << '\n';
  }

  std::string Name;
  float xPosition;
  float yPosition;
  float Velocity{100.0f};
};