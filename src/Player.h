#pragma once
#include <functional>
#include <iostream>
#include <unordered_map>
#include "Subject.h"

enum class PlayerEventType {
    HealthChanged, Died, LevelUp
};

struct PlayerEvent {
    PlayerEventType Type;
    int Value;
};

class Player : public Subject<PlayerEvent> {
    public:

        void TakeDamage(int damage){
            Health -= damage;
            NotifyObservers({
                PlayerEventType::HealthChanged, Health
            });

            if (Health <= 0) {
                NotifyObservers({PlayerEventType::Died, 0});
            }
        }

        void GainExperience(int exp) {
            Experience += exp;
            if (Experience >= 100) {
            Level++;
            Experience -= 100;
            NotifyObservers({
                PlayerEventType::LevelUp, Level
            });
            }
        }
    private:
        int Level{1};
        int Health = 100;
        int Experience{0};
};
