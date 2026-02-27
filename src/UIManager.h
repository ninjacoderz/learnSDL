#pragma once
#include <iostream>
#include "Observer.h"
#include "Player.h"
#include "Network.h"
class UIManager: public Observer<PlayerEvent> , public Observer<NetworkEvent> {
    public: 
        void OnNotify(const PlayerEvent& event) override { 
            if (event.Type == PlayerEventType::HealthChanged) {
                std::cout << "Player Health changed to "
                    << event.Value << '\n';
            }
            if (event.Type == PlayerEventType::LevelUp) {
                std::cout << "Player leveled up to Level "
                    << event.Value << '\n';
            } 
            if (event.Type == PlayerEventType::Died) {
                DisplayGameOverScreen();
            }
        }
        
        void OnNotify(const NetworkEvent& E) override {
            if (E.Type == NetworkEventType::Disconnected) {
            std::cout << "You are offline\n";
            }
        }
    private:
        static void DisplayGameOverScreen() {
            std::cout << "==========================\n";
            std::cout << "        GAME OVER         \n";
            std::cout << "==========================\n";
        }
};