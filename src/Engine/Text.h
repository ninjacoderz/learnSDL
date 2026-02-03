#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Globals.h"

namespace Engine
{
    class Text
    {
    public:
        Text(int x, int y, int w, int h, 
            const std::string& Content,
            SDL_Color Color = { 0, 0, 0, 255},
            float FontSize = 30.0f
        ) : DestinationRect {x, y, w, h}, Color{Color} {
            Font = TTF_OpenFont(Config::FONT.c_str(), FontSize);
            #ifdef SHOW_DEBUG_HELPERS
            Utils::CheckSDLError("TTF_OpenFont");
            #endif
            SetText(Content);
        };

        void SetText( const std::string& Text) {
            SetText(Text, Color);
        }

        void SetText(const std::string& Text, SDL_Color NewColor) {
            if(TextSurface) {
                SDL_DestroySurface(TextSurface);
            }

            Color = NewColor;
            TextSurface = TTF_RenderText_Blended(
                Font, Text.c_str(), 0, Color
            );

            auto [x,y,w,h] = DestinationRect;

            const int WidthDifference{w - TextSurface->w};
            const int LeftOffset{WidthDifference / 2};

            // Vertically centering
            const int HeightDifference{h - TextSurface->h};
            const int TopOffset{HeightDifference / 2};

            TextPosition = {
                x + LeftOffset, y + TopOffset,
                TextSurface->w, TextSurface->h
            };
        }

        void Render(SDL_Surface* Surface) {
            SDL_BlitSurface(
                TextSurface, nullptr, 
                Surface, &TextPosition
            );
        }

        ~Text() {
            if(TTF_WasInit()) {
                TTF_CloseFont(Font); 
            }

            if(TextSurface) {
                SDL_DestroySurface(TextSurface);
            }
        };

        Text(const Text&) = delete;
        Text& operator=(const Text&) = delete;

    private:
        SDL_Surface* TextSurface { nullptr };
        TTF_Font* Font {nullptr};
        SDL_Rect DestinationRect{0, 0, 0,0};
        SDL_Rect TextPosition{0,0,0,0};
        SDL_Color Color{0,0,0,255};
    };
    
} // namespace Engine


#endif