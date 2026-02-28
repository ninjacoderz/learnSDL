#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "GameState.h"
#include "Globals.h"
#include "Engine/Window.h"
#include "SnakeUI.h"

int main(int, char**) {
    SDL_Init(SDL_INIT_VIDEO);
    CheckSDLError("Initializing SDL");

    TTF_Init();
    CheckSDLError("Initializing SDL_ttf");

    Engine::Window GameWindow = Engine::Window();
    // Grid grid = Grid(Assets);
    SnakeUI UI = SnakeUI();
    GameState State = GameState();

    Uint64 PreviousTick{SDL_GetTicks()};
    Uint64 CurrentTick;
    Uint64 DeltaTime;

    SDL_Event Event;
    bool IsRunning = true;
    while (IsRunning) {
        CurrentTick = SDL_GetTicks();
        DeltaTime = CurrentTick - PreviousTick;

        while (SDL_PollEvent(&Event)) {
            UI.HandleEvent(Event);
            State.HandleEvents(Event);
            if (Event.type == SDL_EVENT_QUIT) {
                IsRunning = false;
            }
        }

        State.Update(DeltaTime);
        UI.Update(DeltaTime);

        GameWindow.Render();
        UI.Render(GameWindow.GetSurface());

        GameWindow.Update();

        PreviousTick = CurrentTick;
    }

    TTF_Quit();
    SDL_Quit();
    return 0;
}