#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "IsoMapGame.h"   // ← thay TileMapGame.h
#include "Defs.h"

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768

IsoMapGame* game;         // ← thay TileMapGame

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
            "Couldn't initialize SDL!", SDL_GetError(), NULL);
        return SDL_APP_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("ISO Map",
        SCREEN_WIDTH, SCREEN_HEIGHT,  // ← dùng Defs.h
        SDL_WINDOW_MAXIMIZED);
    if (!window) {
        SDL_Log("SDL_CreateWindow() failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer() failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    game = new IsoMapGame(window, renderer);  // ← thay TileMapGame
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    const int frameTime = 1000 / FPS;

    Uint32 timeStart   = SDL_GetTicks();
    game->RunLoop();
    Uint32 timeEnd     = SDL_GetTicks();
    int    workingTime = timeEnd - timeStart;
    if (workingTime < frameTime) SDL_Delay(frameTime - workingTime);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    game->Shutdown();
    delete game;
}