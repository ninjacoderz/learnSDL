//
// Created by Binh Nguyen Thanh on 7/3/26.
//

#ifndef _SCENE_H
#define _SCENE_H

#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>

#include "Character.h"
#include "Entity.h"

using EntityPtr = std::unique_ptr<Entity>;
using EntityPtrList = std::vector<EntityPtr>;

class Scene {
public:
    Scene() {
        std::string BasePath{SDL_GetBasePath()};
        auto* Player = Entities.emplace_back(std::make_unique<Entity>("Player")).get();
        Player->AddTransformComponent();
        Player->AddImageComponent(BasePath + "player.png");

        EntityPtr &Enemy = Entities.emplace_back(std::make_unique<Entity>("Enemy"));
        Enemy->AddTransformComponent();
        Enemy->AddImageComponent(BasePath + "dragon.png");

        std::cout << "\nDoing something with"
                    " an ImageComponent...";
        // ...


        for (ImageComponent *Component:
             Player->GetImageComponents()) {
            std::cout << "\nDoing something with"
                    " an ImageComponent...";
            // ...
             }

    };

    void HandleEvent(SDL_Event &Event) {
        // Forward event handling to all entities
        for (EntityPtr &Entity: Entities) {
            Entity->HandleEvent(Event);
        }
    }

    void Update(float DeltaTime) {
        for (EntityPtr &Entity: Entities) {
            Entity->Update(DeltaTime);
        }
    }

    void Render(SDL_Surface *Surface) {
        for (EntityPtr &Entity: Entities) {
            Entity->Render(Surface);
        }
    }

private:
    EntityPtrList Entities;
};

#endif //_SCENE_H
