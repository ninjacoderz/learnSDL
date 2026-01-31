#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Window.h"
#include "Image.h"
#include <SDL3_ttf/SDL_ttf.h>
#include "Text.h"
#include "ScaledText.h"
#include "TruncatedText.h"

int main(int, char**) {

  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  Window GameWindow;

  TruncatedText TextExample{
    "The quick brown fox jumps over the lazy dog",
    36.0f,
    GameWindow.GetWidth()
  };

  bool IsRunning = true ; 
  SDL_Event Event; 
  while (IsRunning)
  {
    while (SDL_PollEvent(&Event))
    {
      if( Event.type == SDL_EVENT_QUIT){
        IsRunning = false;
      }
    }
    GameWindow.Render();
    TextExample.Render(GameWindow.GetSurface());
    GameWindow.Update();

  }
  TTF_Quit();
  SDL_Quit();
  return 0;

}