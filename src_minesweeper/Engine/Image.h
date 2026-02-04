#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Globals.h"

namespace Engine
{
    class Image
    {

    public:
        Image(int x, int y, int w, int h,
        const std::string& Filename,
        int Padding = 12) : Destination{
            x + Padding/2, y + Padding/2, w - Padding, h - Padding
        } {

            ImageSurface = IMG_Load(Filename.c_str());
            #ifdef SHOW_DEBUG_HELPERS
                Utils::CheckSDLError("IMG_Load");
            #endif
        };

        void Render(SDL_Surface* Surface) {
            SDL_BlitSurfaceScaled (
                ImageSurface, nullptr,
                Surface, &Destination,
                SDL_SCALEMODE_LINEAR
            );
        }

        ~Image() {
            if(ImageSurface) {
                SDL_DestroySurface(ImageSurface);
            }
        };
        
        Image(const Image&);
        Image& operator=(const Image&);

    private:
        SDL_Surface* ImageSurface{nullptr};
        SDL_Rect Destination { 0, 0, 0, 0 };
    };
    
} // namespace Engine


#endif