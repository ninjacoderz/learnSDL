#ifndef WRAPPEDTEXT_H
#define WRAPPEDTEXT_H

#include <string>
#include "Text.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class WrappedText : public Text
{

public:
    WrappedText(
        const std::string& Content,
        float FontSize,
        int MaxWidth)
        :Text{FontSize}, MaxWidth{MaxWidth} {
            CreateSurface(Content);
        };
    ~WrappedText() {};
    
private:
    void CreateSurface(const std::string& Content) {
        SDL_DestroySurface ( TextSurface );
        TextSurface = TTF_RenderText_Blended_Wrapped (
            Font, Content.c_str(), 0, {225, 255, 255, 255}, MaxWidth
        );

        if(!TextSurface){
            std::cout << "Error creating TextSurface: "
                << SDL_GetError() << '\n';
        }
    }
    int MaxWidth;
};

#endif