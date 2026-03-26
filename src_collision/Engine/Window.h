//
// Created by Binh Nguyen Thanh on 7/3/26.
//

#ifndef _WINDOW_H
#define _WINDOW_H

#pragma once
#include <iostream>
#include <SDL3/SDL.h>

class Window {
public:
    Window() {
        SDLWindow = SDL_CreateWindow(
          "Composition Example",
          1024, 768, 0
        );
        if (!SDLWindow) {
            std::cerr << "Window could not be created! SDL_Error: "
              << SDL_GetError() << std::endl;
        }
    }

    ~Window() {
        if (SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
            SDL_DestroyWindow(SDLWindow);
        }
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void Render() {
        const auto* Fmt{SDL_GetPixelFormatDetails(
          GetSurface()->format
        )};
        SDL_FillSurfaceRect(
          GetSurface(), nullptr,
          SDL_MapRGB(Fmt, nullptr, 220, 220, 220));
    }

    void Update() const {
        SDL_UpdateWindowSurface(SDLWindow);
    }

    SDL_Surface* GetSurface() {
        if (SDLWindow) {
            return SDL_GetWindowSurface(SDLWindow);
        }
        return nullptr;
    }

private:
    SDL_Window* SDLWindow = nullptr;
};

#endif //_WINDOW_H