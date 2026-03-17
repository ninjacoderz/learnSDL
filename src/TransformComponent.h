//
// Created by Binh Nguyen Thanh on 9/3/26.
//

#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H
#include <iostream>
#include "Utilities.h"
#include "Component.h"
#include "Vec2.h"

class TransformComponent: public Component {
public:
    using Component::Component;

    ~TransformComponent() override = default;

    void Update(float DeltaTime) override {
        std::cout << "TransformComponent Updated\n " << std::endl;
    }

    Vec2 GetPosition() const {
        return Position;
    }

    void SetPosition(const Vec2& position) {
        Position = position;
    }

    void Move(const Vec2& Delta) {
        Position += Delta;
    }

    void DrawDebugHelpers(SDL_Surface* S) override {
        auto [x, y]{GetPosition()};
        SDL_Rect Square{Utilities::Round({
          x - 10, y - 10, 20, 20
        })};
        SDL_FillSurfaceRect(S, &Square, SDL_MapRGB(
          SDL_GetPixelFormatDetails(S->format),
          nullptr, 255, 0, 0));
    }
private:
    Vec2 Position = {0, 0};
};

#endif //_TRANSFORMCOMPONENT_H