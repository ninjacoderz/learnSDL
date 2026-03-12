//
// Created by Binh Nguyen Thanh on 7/3/26.
//

#ifndef _COMPONENT_H
#define _COMPONENT_H

#pragma once
#include <SDL3/SDL.h>
class Entity;

class Component {
public:
    explicit Component(Entity* Owner) : Owner(Owner) {}
    Component() = default;
    virtual ~Component() = default;

    virtual void Initialize() {}
    virtual void OnComponentRemoved() {}
    virtual void Update(float DeltaTime) {};
    virtual void Render(SDL_Surface* surface) {};
    virtual void HandleEvent(const SDL_Event& event) {};

    Entity* GetOwner() const { return Owner; }

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

class PhysicsComponent : public Component {
public:
    using Component::Component;
    void Update(float DeltaTime) override;
};

#endif //_COMPONENT_H