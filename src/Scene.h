//
// Created by Binh Nguyen Thanh on 7/3/26.
//

#ifndef _SCENE_H
#define _SCENE_H

#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "Entity.h"
#include "AssetManager.h"

using EntityPtr = std::unique_ptr<Entity>;
using EntityPtrList = std::vector<EntityPtr>;

class Scene {
public:
    Scene() {
        std::string BasePath{SDL_GetBasePath()};

        EntityPtr& Player{Entities.emplace_back(
          std::make_unique<Entity>(*this))};
        Player->AddTransformComponent()
              ->SetPosition({100, 240});

        ImageComponent* PlayerImage{
            Player->AddImageComponent(BasePath + "player.png")
          };

        PlayerImage->SetOffset({
          PlayerImage->GetSurfaceWidth() * -0.5f,
          PlayerImage->GetSurfaceHeight() * -0.5f
        });

        EntityPtr& Enemy{Entities.emplace_back(
          std::make_unique<Entity>(*this))};
        Enemy->AddTransformComponent()
             ->SetPosition({250, 20});
        Enemy->AddImageComponent(BasePath + "dragon.png");
    }

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

    AssetManager& GetAssetManager() {
        return Assets;
    }

private:
    EntityPtrList Entities;
    AssetManager Assets;
};

#endif //_SCENE_H
