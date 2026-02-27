#pragma once
#include <iostream>
#include "Subject.h"

enum class NetworkEventType {
  Connected,
  Disconnected
};

struct NetworkEvent {
  NetworkEventType Type;
};

class NetworkManager : public Subject<NetworkEvent> {
 public:
  void Disconnect() {
    std::cout << "Network Disconnected\n";
    NotifyObservers({
      NetworkEventType::Disconnected
    });
  }
};