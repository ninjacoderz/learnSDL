#pragma once
#include <SDL3/SDL.h>

#include "Assets.h"
#include "Snake/Grid.h"
#include "Snake/RestartButton.h"
#include "Snake/ScoreCounter.h"

class SnakeUI {
   public:

    SnakeUI() : Grid(AssetList),
    ScoreCounter{AssetList},
    RestartButton(
        Config::WINDOW_WIDTH - 150,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        150 - Config::PADDING,
        Config::FOOTER_HEIGHT - Config::PADDING
    ) {
    };

    ~SnakeUI(){};

    void HandleEvent(const SDL_Event& event) {
        Grid.HandleEvents(event);
        RestartButton.HandleEvents(event);
        ScoreCounter.HandleEvent(event);
    }
    void Update(Uint64 DeltaTime) {
        Grid.Update(DeltaTime);
    }
    void Render(SDL_Surface* Surface) {
        Grid.Render(Surface);
        ScoreCounter.Render(Surface);
        RestartButton.Render(Surface);
    }

   private:
    Assets AssetList;
    Grid Grid;
    RestartButton RestartButton;
    ScoreCounter ScoreCounter;
};
