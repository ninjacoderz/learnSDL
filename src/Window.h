#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class Window {
    public: 
        Window();
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        
        SDL_Surface* GetSurface() const;
        void Render();
        void Update();

        int GetWidth() const { return WindowWidth; }
        int GetHeight() const { return 300; }

        void TakeScreenshot() const {
            IMG_SaveJPG(
            GetSurface(), "Screenshot.jpg", 90
            );
        }
    private: 
        SDL_Window* mSDL_Window = nullptr;
        int WindowWidth{600};
};

#endif