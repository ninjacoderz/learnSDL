
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL3/SDL.h>
namespace Engine
{
    class Rectangle
    {
    public:
        Rectangle(int x, int y, int w, int h,
            SDL_Color Color = { 0, 0, 0, 255 }
        ): Rect{x, y, w, h}, Color{Color}{}
        
        virtual void Render(SDL_Surface* Surface){
            const auto* fmt = SDL_GetPixelFormatDetails(
                Surface->format
            );

            SDL_FillSurfaceRect(
                Surface, &Rect, SDL_MapRGB(fmt, nullptr, Color.r, Color.g, Color.b)
            );
        }

        void SetColor(SDL_Color C){ Color = C; }

        bool IsWithinBounds(int x, int y) const {
            if(x < Rect.x) return false;
            if(x > Rect.x + Rect.w) return false;
            if(y < Rect.y) return false;
            if(y > Rect.y + Rect.h) return false;
            return true;
        }

        const SDL_Rect* GetRect() const { return &Rect; }

        virtual ~Rectangle() = default;
        
    private:
        SDL_Rect Rect{0, 0, 0 , 0};
        SDL_Color Color = {0, 0, 0, 0};
    };
    
    
} // namespace Engine

#endif