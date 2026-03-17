//
// Created by Binh Nguyen Thanh on 15/3/26.
//

#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <memory> // for std::shared_ptr
#include <string>
#include <unordered_map>
#include "SDL3_image/SDL_image.h"

struct SDLSurfaceDeleter {
    void operator()(SDL_Surface* surface) const {
        SDL_DestroySurface(surface);
    }
};

using SurfacePtr = std::shared_ptr<SDL_Surface>;
using CacheMap = std::unordered_map<std::string, SurfacePtr>;

class AssetManager {
public:
    AssetManager() = default;
    SurfacePtr LoadSurface(const std::string& Path) {
        if (SurfaceCache.contains(Path)) {
            std::cout << "CACHE HIT: " << Path << '\n';
            return SurfaceCache[Path];
        }
        // Cache Miss - need to load a new surface
        std::cout << "CACHE MISS: " << Path << '\n';
        SDL_Surface* Surface = IMG_Load(Path.c_str());
        if (!Surface) {
            std::cerr << "AssetManager failed to load: "
                      << Path << " Error: "
                      << SDL_GetError() << '\n';
            return nullptr;  // Return null on failure
        }

        SurfacePtr SharedSurface = SurfacePtr(Surface, SDLSurfaceDeleter{});
        SurfaceCache[Path] = SharedSurface;
        return SharedSurface;
    };

    // Prevent copying/moving
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = delete;
    AssetManager& operator=(AssetManager&&) = delete;
private:
    CacheMap SurfaceCache;
};
#endif //_ASSETMANAGER_H