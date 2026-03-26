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

        // --- Falling Entity ---
        EntityPtr &Player{
            Entities.emplace_back(
                std::make_unique<Entity>(*this)
            )
        };

        Player->AddTransformComponent()
                ->SetPosition({
                    2.f * PIXELS_PER_METER,
                    1.f * PIXELS_PER_METER,
                });
        Player->AddPhysicsComponent()
                ->SetMass(50.0);
        Player->AddImageComponent(BasePath + "player.png");
        Player
                ->AddCollisionComponent()
                // Match rough image size
                ->SetSize(
                    1.9f * PIXELS_PER_METER,
                    1.7f * PIXELS_PER_METER
                );

        // --- Static Entity ---
        EntityPtr &Floor{
            Entities.emplace_back(
                std::make_unique<Entity>(*this)
            )
        };

        Floor->AddTransformComponent()
                ->SetPosition({
                    1.f * PIXELS_PER_METER,
                    4.f * PIXELS_PER_METER,
                });
        // Add an image - optional - we can see where the
        // the object is based on the collision component
        // drawn by DrawDebugHelpers()
        Floor->AddImageComponent(BasePath + "floor.png");
        Floor
                ->AddCollisionComponent()
                ->SetSize(
                    5.0f * PIXELS_PER_METER,
                    2.0f * PIXELS_PER_METER
                );

        // Note the floor has no physics component
        // so will not be affected by gravity
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

        CheckCollisions();
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

    AssetManager &GetAssetManager() {
        return Assets;
    }

#ifdef DRAW_DEBUG_HELPERS
    SDL_Surface *Trajectories{
        SDL_CreateSurface(
            700, 300, SDL_PIXELFORMAT_RGBA32
        )
    };
#endif

private:
    EntityPtrList Entities;
    AssetManager Assets;

    void CheckCollisions();
};

#endif //_SCENE_H
