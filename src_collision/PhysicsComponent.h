//
// Created by Binh Nguyen Thanh on 18/3/26.
//

#ifndef _PHYSICSCOMPONENT_H
#define _PHYSICSCOMPONENT_H

#pragma once
#include "Component.h"
#include "Vec2.h"

class PhysicsComponent : public Component {
public:
    // Inherit constructor
    using Component::Component;

    Vec2 GetVelocity() const { return Velocity; }
    void SetVelocity(const Vec2& NewVelocity) {
        Velocity = NewVelocity;
    }

    float GetMass() const { return Mass; }
    void SetMass(float NewMass);

    void ApplyForce(const Vec2& Force);
    // Apply impulse - affects velocity directly
    void ApplyImpulse(const Vec2& Impulse);
    void Update(float DeltaTime) override;
    void Initialize() override;

    void DrawDebugHelpers(SDL_Surface* Surface) override;
private:
    Vec2 Velocity{0.0, 0.0}; // m/s
    Vec2 Acceleration{0.0, 0.0}; // m/s^2
    float Mass{1.0}; // kg, default to 1kg
};

#endif //_PHYSICSCOMPONENT_H