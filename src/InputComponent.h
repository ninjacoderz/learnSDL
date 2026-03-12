//
// Created by Binh Nguyen Thanh on 12/3/26.
//

#ifndef _INPUTCOMPONENT_H
#define _INPUTCOMPONENT_H

#pragma once
#include "Component.h"

class InputComponent : public Component {
    public:
    using Component::Component;

    void HandleEvent(const SDL_Event &event) override;
};

#endif //_INPUTCOMPONENT_H
