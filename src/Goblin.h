#pragma once
#include <iostream>
#include <string>
#include "GameObject.h"

class Goblin: public GameObject {
public: 
    Goblin(const std::string& name, int x, int y) : 
        Name{name}, xPosition{x}, yPosition{y}{};

    void Tick() override {
        std::cout << "\nTick() updating position";
        xPosition += 1;
    }

    void Render(SDL_Surface* Surface) override {
        std::cout  << " - Rendering at x = " << xPosition;
    }

    std::string Name;
    int xPosition;
    int yPosition;
    
};