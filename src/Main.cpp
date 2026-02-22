#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Window.h"
#include "World.h"

struct GameState {
  Window GameWindow;
  World GameWorld;
  bool IsRunning{true};
  Uint64 PreviousFrame{0};
};

SDL_AppResult SDL_AppInit( void** AppState, int, char** ) {
  SDL_Init(SDL_INIT_VIDEO);
  GameState* State{ new GameState()};
  State->GameWorld.SpawnGoblin("Goblin Rogue", 100, 200);
  State->PreviousFrame = SDL_GetTicks();
  *AppState = State;
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* AppState, SDL_Event* Event ){
  GameState* State = static_cast<GameState*>(AppState);
  if (Event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  } else {
    State->GameWorld.HandleEvent(*Event);
  }
  
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void * AppState) {
  GameState* State = static_cast<GameState*>(AppState);
  Uint64 ThisFrame = SDL_GetTicks();
  Uint64 TimeDelta = ThisFrame - State->PreviousFrame;
  State->GameWorld.Tick(TimeDelta / 1000.0f);
  State->GameWindow.Render() ;
  State->GameWorld.Render(
    State->GameWindow.GetSurface()
  );
  State->GameWindow.Update();
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(
  void* AppState, SDL_AppResult Result
) {
  delete static_cast<GameState*>(AppState);
}