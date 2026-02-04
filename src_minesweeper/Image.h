#ifndef IMAGE_H
#define IMAGE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>

class Image {
public:
  Image(const std::string& File);

  void Render(SDL_Surface* DestinationSurface) {
    if (!ImageSurface) return;
    SDL_BlitSurfaceScaled(
      ImageSurface, nullptr,
      DestinationSurface, &DestinationRectangle,
      SDL_SCALEMODE_LINEAR
    );
  }

  ~Image();
  

  void SaveToFile(const std::string& Location) const {
    if (!ImageSurface) return;
    IMG_SavePNG(ImageSurface, Location.c_str());
  }
  
  Image(const Image&);
  Image& operator=(const Image&);

private:
  SDL_Surface* ImageSurface{nullptr};
  SDL_Rect DestinationRectangle{200, 50, 100, 100};
};

#endif