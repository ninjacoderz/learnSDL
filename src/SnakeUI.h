#pragma once
#include <SDL3/SDL.h>

#include "Assets.h"
#include "Snake/Grid.h"

class SnakeUI {
   public:

    SnakeUI() : Grid(AssetList){};
    ~SnakeUI(){};

    void HandleEvent(const SDL_Event& event) {
        Grid.HandleEvents(event);
    }
    void Update(Uint64 DeltaTime) {
        Grid.Update(DeltaTime);
    }
    void Render(SDL_Surface* Surface) {
        Grid.Render(Surface);
    }

   private:
    Assets AssetList;
    Grid Grid;
};