//
// Created by Binh Nguyen Thanh on 18/3/26.
//

#ifndef _COLLISIONCOMPONENT_H
#define _COLLISIONCOMPONENT_H

#pragma once
#include "Component.h"
#include "Vec2.h"
#include <SDL3/SDL.h>

class CollisionComponent : public Component {
public:
    using Component::Component;
    void SetOffset(const Vec2& offset);
    void SetSize(float NewWidth, float NewHeight);
    const SDL_FRect& GetBounds() const;
    void Initialize() override;
    void Update(float DeltaTime) override;

    bool IsCollidingWith(const CollisionComponent& Other) const;
    bool GetCollisionRectangle(
       const CollisionComponent& Other,
       SDL_FRect* OutIntersection
    ) const;
    void DrawDebugHelpers(SDL_Surface* Surface) override;
private:
    Vec2 Offset{0.0, 0.0};
    float Width{1.0};
    float Height{1.0};
    SDL_FRect Bounds{0.0, 0.0, 0.0, 0.0};
};

#endif //_COLLISIONCOMPONENT_H