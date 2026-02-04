#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>
#include "../Globals.h"

namespace Engine { 
    class  Window
    {
    public:
        Window(){
            SDLWindow = SDL_CreateWindow (
                Config::GAME_NAME.c_str(),
                Config::WINDOW_WIDTH,
                Config::WINDOW_HEIGHT,
                0
            );
        }
        
        void Render() {
            const auto fmt = SDL_GetPixelFormatDetails (
                GetSurface() -> format
            );
            SDL_FillSurfaceRect(
                GetSurface(), nullptr,
                SDL_MapRGB(fmt, nullptr, 
                    Config::BACKGROUP_COLOR.r,
                    Config::BACKGROUP_COLOR.g,
                    Config::BACKGROUP_COLOR.b
                )
            );
        }

        void Update(){
            SDL_UpdateWindowSurface(SDLWindow);
        }

        SDL_Surface* GetSurface() const {
            return SDL_GetWindowSurface(SDLWindow);
        }

        ~Window(){
            if(SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
                SDL_DestroyWindow(SDLWindow);
            }
        }

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

    private:
        SDL_Window* SDLWindow{nullptr};
    };
}
#endif