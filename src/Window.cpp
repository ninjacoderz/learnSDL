#include "Window.h"
Window::Window()
{
    mSDL_Window = SDL_CreateWindow(
        "My FarmGame", WindowWidth, 300, SDL_WINDOW_RESIZABLE
    );
}

Window::~Window()
{
    if(mSDL_Window)
        SDL_DestroyWindow(mSDL_Window);
}

SDL_Surface *Window::GetSurface() const
{
    return SDL_GetWindowSurface(mSDL_Window);    
}

void Window::Render()
{
    const auto* Fmt = SDL_GetPixelFormatDetails(
      GetSurface()->format
    );

    SDL_FillSurfaceRect(
      GetSurface(),
      nullptr,
      SDL_MapRGB(Fmt, nullptr, 50, 50, 50)
    );
}

void Window::Update()
{
    SDL_UpdateWindowSurface(mSDL_Window);
}
