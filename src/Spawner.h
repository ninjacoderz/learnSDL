#pragma once 
#include <SDL3/SDL.h>
#include <iostream>

class Spawner
{

public:
    void HandleKeyDownEvent(SDL_KeyboardEvent& E) {
        std::cout << "Button Pressed\n";
    }
private:
    /* data */
};

