//
// Created by Binh Nguyen Thanh on 7/3/26.
//

#ifndef _COMPONENT_H
#define _COMPONENT_H

#pragma once
#include <SDL3/SDL.h>

#include "Vec2.h"

class Scene;
class Entity;
class AssetManager;
class Component {
public:
    explicit Component(Entity* Owner) : Owner(Owner) {}
    Component() = default;
    virtual ~Component() = default;

    virtual void Initialize() {}
    virtual void OnComponentRemoved(Component * component) {}
    virtual void Update(float DeltaTime) {}

    virtual void Render(SDL_Surface* surface) {};
    virtual void HandleEvent(const SDL_Event& event) {};

    virtual void DrawDebugHelpers(SDL_Surface* Surface) {}
    float GetOwnerScale() const;

    Vec2 GetOwnerPosition() const;
    void SetOwnerPosition(const Vec2& position);
    Entity* GetOwner() const { return Owner; }
    AssetManager& GetAssetManager() const;
    Scene& GetScene() const;
protected:
    Entity* Owner = nullptr;
};

class AnimationComponent : public Component {
public:
    using Component::Component;
    void Update(float DeltaTime) override;
};

class AudioComponent : public Component {
public:
    using Component::Component;
    void Update(float DeltaTime) override;
};

#endif //_COMPONENT_H