//
// Created by Binh Nguyen Thanh on 12/3/26.
//

#include <iostream>
#include <SDL3/SDL.h>
#include "InputComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace {
    // Factory function for moving left (negative X)
    CommandPtr CreateMoveLeftCommand() {
        return std::make_unique<MovementCommand>(
            Vec2{-5.0, 0.0});
    }

    // Factory function for moving right (positive X)
    CommandPtr CreateMoveRightCommand() {
        return std::make_unique<MovementCommand>(
            Vec2{5.0, 0.0});
    }
}

void InputComponent::Initialize() {
    Component::Initialize();
    BindKeyDown(SDLK_LEFT, CreateMoveLeftCommand);
    BindKeyDown(SDLK_RIGHT, CreateMoveRightCommand);
}

void InputComponent::HandleEvent(const SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (!GetOwner()) return;
        if (const SDL_Keycode Key{event.key.key}; KeyDownBindings.contains(Key)) {
            CommandPtr Command{KeyDownBindings[Key]()};
            Owner->HandleCommand(std::move(Command));
        }
    }
}
