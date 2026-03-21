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

    static inline int PIXELS_PER_METER{50};
    static inline Vec2 GRAVITY = Vec2(0, 9.8 * PIXELS_PER_METER);

    Scene() {
        std::string BasePath{SDL_GetBasePath()};
        EntityPtr& Player{Entities.emplace_back(
          std::make_unique<Entity>(*this)
        )};

        Player->AddTransformComponent()
              ->SetPosition({100.f, 150.f});

        // Add physics
        PhysicsComponent* Physics{
            Player->AddPhysicsComponent()
          };

        // Make it 50kg
        Physics->SetMass(50);

        // Set initial velocity
        Physics->SetVelocity({
          5.f * PIXELS_PER_METER, -7.f * PIXELS_PER_METER
        });

        // Add an image to see it
        Player->AddImageComponent(BasePath + "player.png");
        Player->AddInputComponent();
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

#ifdef DRAW_DEBUG_HELPERS
        SDL_BlitSurface(
          Trajectories, nullptr, Surface, nullptr
        );
#endif
    }

    AssetManager& GetAssetManager() {
        return Assets;
    }

#ifdef DRAW_DEBUG_HELPERS
    SDL_Surface* Trajectories{
        SDL_CreateSurface(
          700, 300, SDL_PIXELFORMAT_RGBA32
        )
      };
#endif
private:
    EntityPtrList Entities;
    AssetManager Assets;
};

#endif //_SCENE_H
