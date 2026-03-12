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
        EntityPtr &NewEntity{
            Entities.emplace_back(
                std::make_unique<Entity>("Test")
            )
        };
        NewEntity->AddImageComponent();
        NewEntity->AddImageComponent();
        NewEntity->AddImageComponent();
        NewEntity->AddTransformComponent();
        std::cout << "Image Component Count: "
                << std::ranges::distance(
                    NewEntity->GetImageComponents());

        for (ImageComponent *Component:
             NewEntity->GetImageComponents()) {
            std::cout << "\nDoing something with"
                    " an ImageComponent...";
            // ...
             }

        EntityPtr& NewCharacter = Entities.emplace_back(
            std::make_unique<Character>()
        );
        NewCharacter->AddImageComponent();
        NewCharacter->AddImageComponent();
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
