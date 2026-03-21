//
// Created by Binh Nguyen Thanh on 12/3/26.
//

#include <iostream>
#include <SDL3/SDL.h>
#include "InputComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Scene.h"

namespace {
    const float SPEED = 5.f * Scene::PIXELS_PER_METER;
    // Factory function for moving left (negative X)
    CommandPtr CreateMoveLeftCommand() {
        return std::make_unique<MovementCommand>(
            Vec2{-SPEED, 0.0}
        );
    }

    // Factory function for moving right (positive X)
    CommandPtr CreateMoveRightCommand() {
        return std::make_unique<MovementCommand>(
            Vec2{SPEED, 0.0}
        );
    }
}

CommandPtr CreateJumpCommand() {
    // Example value in kg*m/s
    const float JUMP_IMPULSE_MAGNITUDE{
        -500.f * Scene::PIXELS_PER_METER
      };
    // Return a jump command instead of movement
    return std::make_unique<JumpCommand>(
      Vec2{0.0, JUMP_IMPULSE_MAGNITUDE}
    );
}


void InputComponent::Initialize() {
    Component::Initialize();
    BindKeyDown(SDLK_LEFT, CreateMoveLeftCommand);
    BindKeyDown(SDLK_RIGHT, CreateMoveRightCommand);
    BindKeyDown(SDLK_SPACE, CreateJumpCommand);
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
