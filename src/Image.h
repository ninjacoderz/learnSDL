//
// Created by Binh Nguyen Thanh on 26/3/26.
//

#ifndef PHYSICALMOTION_IMAGE_H
#define PHYSICALMOTION_IMAGE_H

#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>
#include "Vec2.h"
class Image {
public:
    Image() = default;
    Image(const std::string& ImagePath, float Scale): Scale(Scale) {
        std::string BasePath{SDL_GetBasePath()};
        ImageSurface = IMG_Load((BasePath + ImagePath).c_str());
        if (!ImageSurface) {
            std::cout << "Error creating image: "
              << SDL_GetError();
        }
    }

    void Render(
      SDL_Surface* Surface, const Vec2& Pos
    ) {
        if (ImageSurface) {
            SDL_Rect SrcRect{
                0, 0,
                ImageSurface->w, ImageSurface->h
              };
            SDL_Rect DestRect{
                int(Pos.x), int(Pos.y),
                int(ImageSurface->w * Scale), int(ImageSurface->h * Scale)
              };
            SDL_BlitSurfaceScaled(
              ImageSurface, &SrcRect, Surface, &DestRect, SDL_SCALEMODE_LINEAR);
        }
    }

    // Move constructor
    Image(Image&& Other) noexcept
    : ImageSurface(Other.ImageSurface) {
        Other.ImageSurface = nullptr;
    }

    ~Image() {
        if (ImageSurface) {
            SDL_DestroySurface(ImageSurface);
        }
    }

    // Prevent copying
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

private:
    SDL_Surface* ImageSurface{nullptr};
    float Scale = 1.0f;
};

#endif //PHYSICALMOTION_IMAGE_H