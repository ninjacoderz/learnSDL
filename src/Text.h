#ifndef TEXT_H 
#define TEXT_H
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>

class Text
{    
public:
    Text(const std::string& Content,
        float FontSize = 100.0f
    ): Font{LoadFont(FontSize)} {
        CreateSurface(Content);
    };

    void SetFontSize(float NewSize) {
        TTF_SetFontSize(Font, NewSize);
    }
    
    void Render(SDL_Surface* DestinationSurface){
        SDL_BlitSurface(
            TextSurface, nullptr,
            DestinationSurface, nullptr
        );
    };

    ~Text(){
        SDL_DestroySurface(TextSurface);
        if (TTF_WasInit()) {
            TTF_CloseFont(Font);
        }
    };

    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;

protected:

    Text(float FontSize)
        : Font{LoadFont(FontSize)} {}
    
    TTF_Font* LoadFont(float FontSize) {
        TTF_Font* LoadedFont{TTF_OpenFont("Roboto-Medium.ttf", FontSize)};
        if (!LoadedFont) {
            std::cout << "Error loading font: "
                << SDL_GetError() << '\n';
        }
        return LoadedFont;
    } 

    void CreateSurface(const std::string& Content) {
        SDL_Surface* NewSurface{TTF_RenderText_LCD(
            Font, Content.c_str(), 0, {255, 255, 255, 255}, {0, 0, 90, 255} 
        )};
        if (NewSurface) {
            SDL_DestroySurface(TextSurface);
            TextSurface = NewSurface;
        } else {
            std::cout << "Error creating TextSurface: "
                << SDL_GetError() << '\n';
        }
    }

    SDL_Surface* TextSurface{nullptr};
    TTF_Font* Font{nullptr};
    SDL_Rect DestinationRect = SDL_Rect{50, 50, 400, 200};
};

#endif