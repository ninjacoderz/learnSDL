//
// Created by Binh Nguyen Thanh on 26/3/26.
//

#ifndef PHYSICALMOTION_SCENE_H
#define PHYSICALMOTION_SCENE_H

#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "GameObject.h"
#include "Config.h"

class Scene {
public:
    Scene() {
        Objects.emplace_back(
            "dwarf.png", Vec2{
                3.0f * PIXELS_PER_METER,
                2.0f * PIXELS_PER_METER
            }, *this, 0.15f
        );
    }

    void HandleEvent(SDL_Event &E) {
        for (GameObject &Object: Objects) {
            Object.HandleEvent(E);
        }
    }

    void Tick(float DeltaTime) {
        for (GameObject &Object: Objects) {
            Object.Tick(DeltaTime);
        }
    }

    void Render(SDL_Surface *Surface) {
        for (GameObject &Object: Objects) {
            Object.Render(Surface);
        }
    }

private:
    std::vector<GameObject> Objects;
};

#endif //PHYSICALMOTION_SCENE_H
