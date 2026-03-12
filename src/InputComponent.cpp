//
// Created by Binh Nguyen Thanh on 12/3/26.
//

#include <iostream>
#include <SDL3/SDL.h>
#include "InputComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

void InputComponent::HandleEvent(const SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (!GetOwner()) return;
        TransformComponent* Transform = GetOwner()->GetComponent<TransformComponent>();
        if (!Transform) return;

        switch (event.key.key) {
            case SDLK_LEFT:
                Transform->Move({-1.0, 0.0});
                std::cout << "InputComponent::HandleEvent: Left key down" << std::endl;
                break;
            case SDLK_RIGHT:
                Transform->Move({1.0, 0.0});
                std::cout << "InputComponent::HandleEvent: Right key down" << std::endl;
                break;
            default:
                break;
        }
    }
}