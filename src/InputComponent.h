//
// Created by Binh Nguyen Thanh on 12/3/26.
//

#ifndef _INPUTCOMPONENT_H
#define _INPUTCOMPONENT_H

#pragma once
#include "Component.h"
#include <functional>
#include <memory>

class Command;
using CommandPtr = std::unique_ptr<Command>;
using CommandFactory = std::function<CommandPtr()>;
using KeyToFactoryMap = std::unordered_map<SDL_Keycode, CommandFactory>;

class InputComponent : public Component {
public:
    using Component::Component;
    void Initialize() override;
    void HandleEvent(const SDL_Event &event) override;
    void BindKeyDown(
        SDL_Keycode Key, CommandFactory Factory
    ) {
        KeyDownBindings[Key] = Factory;
    }
private:
    KeyToFactoryMap KeyDownBindings;
};

#endif //_INPUTCOMPONENT_H
