#pragma once
#include <iostream>
#include <functional>

class Player {
    public:
    void TakeDamage(int Damage) {
        Health -= Damage;
        if(DefeatCallBack && Health < 0) {
            DefeatCallBack(Health);
        }
    }
    int Health;
    std::function<void(int i)> DefeatCallBack {nullptr};
};