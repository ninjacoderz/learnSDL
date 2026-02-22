#pragma once
#include <SDL3/SDL.h>

class GameObject {
    public: 
        virtual void HandleEvent(const SDL_Event& Event){ 
            //
        }
        virtual void Tick(float TimeDelta) {}
        
        virtual void Render(SDL_Surface* Surface) {

        }
};

