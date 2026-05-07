//
// Created by Binh Nguyen Thanh on 26/3/26.
//

#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#pragma once
#include <SDL3/SDL.h>

#include "Config.h"
#include "Vec2.h"
#include "Image.h"

class Scene;

class GameObject {
public:
    GameObject(
        const std::string &ImagePath,
        const Vec2 &InitialPosition,
        const Scene &Scene,
        float Scale) : Image{ImagePath, Scale},
                       Position{InitialPosition},
                       Scene{Scene}, Scale(Scale) {
    }

    void HandleEvent(SDL_Event &E) {
    }

    void Tick(float DeltaTime) {
        Position += Velocity * DeltaTime;
    }

    void Render(SDL_Surface *Surface);

    Vec2 Position;
    Vec2 Velocity{ 2.0f * PIXELS_PER_METER, 0.0f};

private:
    Image Image;
    const Scene &Scene;
    float Scale = 1.0f;
};

#endif //_GAMEOBJECT_H
