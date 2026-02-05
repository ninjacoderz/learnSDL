#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

#include "World.h"
#include "GameObject.h"
#include "Window.h"
#include "Goblin.h"

int main(int, char**) {
  SDL_Init(SDL_INIT_VIDEO);

  Window GameWindow;
  World GameWorld;

  Goblin& Enemy{GameWorld.SpawnGoblin(
    "Goblin Rogue", 100, 200)};
  std::cout << "A " << Enemy.Name
    << " was spawned in the world";

  bool IsRunning = true;
  SDL_Event Event;
  while (IsRunning) {
    while (SDL_PollEvent(&Event)) {
      if (Event.type == SDL_EVENT_QUIT) {
        IsRunning = false;
      }
      GameWorld.HandleEvent(Event);
    }

    GameWorld.Tick();

    GameWindow.Render();
    GameWorld.Render(GameWindow.GetSurface());

    GameWindow.Update();
  }

  SDL_Quit();
  return 0;
}