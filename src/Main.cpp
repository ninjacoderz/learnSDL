// main.cpp
#include "UIManager.h"
#include "Player.h"

int main() {
  Player PlayerOne;
  UIManager UI;
  NetworkManager Network;

  int ObserverID = PlayerOne.AddObserver(&UI);
  int NetObserverKey = Network.AddObserver(&UI);
  // Simulate some game actions
  PlayerOne.TakeDamage(30);
  PlayerOne.GainExperience(150);
  PlayerOne.TakeDamage(100);

  // Remove the observer using the key
  PlayerOne.RemoveObserver(ObserverID);

  // UI is no longer observing
  PlayerOne.GainExperience(100);
  Network.Disconnect();
}