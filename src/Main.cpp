#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Engine/Window.h"
#include "Scene.h"

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    Window GameWindow;
    Scene GameScene;

    Uint64 LastTick = SDL_GetPerformanceCounter();
    bool IsRunning = true;
    SDL_Event Event;

    const float TargetFPS = 60.0f;
    const float TargetFrameTime = 1.0f / TargetFPS; // ~0.0166s

    while (IsRunning) {
        while (SDL_PollEvent(&Event)) {
            if (Event.type == SDL_EVENT_QUIT) {
                IsRunning = false;
            }
            GameScene.HandleEvent(Event);
        }

        Uint64 CurrentTick = SDL_GetPerformanceCounter();
        float DeltaTime = static_cast<float>(CurrentTick - LastTick) /
                          (float)SDL_GetPerformanceFrequency();
        LastTick = CurrentTick;

        // Tick
        GameScene.Update(DeltaTime);

        // Render
        GameWindow.Render();
        GameScene.Render(GameWindow.GetSurface());
        // Swap
        GameWindow.Update();

        Uint64 Entick = SDL_GetPerformanceCounter();
        float FrameTime = (float)(Entick - CurrentTick) / (float)SDL_GetPerformanceFrequency();

        if (FrameTime > TargetFrameTime) {
            Uint32 DelayMs = (Uint32)(TargetFrameTime - FrameTime * 1000.0f);
            if (DelayMs > 0) {
                SDL_Delay(DelayMs);
            }
        }
    }

    SDL_Quit();
    return 0;
}
