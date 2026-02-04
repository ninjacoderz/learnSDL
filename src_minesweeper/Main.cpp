#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Globals.h"
#include "Engine/Window.h"
#include "Minesweeper/UI.h"

int main(int, char**) {

  SDL_Init(SDL_INIT_VIDEO);

  #ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("SDL_Init");
  #endif

  TTF_Init();

  #ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("TTF_Init");
  #endif

  Engine::Window GameWindow;
  MinesweeperUI UI;

  SDL_Event Event;
  bool shouldQuit{false};
  


  GameWindow.Render();
    
  
  while (!shouldQuit)
  {
      SDL_Event Event;
      if (SDL_WaitEvent(&Event)) {
          if (Event.type == SDL_EVENT_QUIT) {
              shouldQuit = true;
          } else {
              UI.HandleEvent(Event);
          }
          UI.Render(GameWindow.GetSurface());
          GameWindow.Update(); 
      }
  }

  TTF_Quit();
  SDL_Quit();
  return 0;

}