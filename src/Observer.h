#pragma once
#include <iostream>

template <typename EventType>

class Observer {
 public:
  virtual void OnNotify(const EventType& E) {}
};