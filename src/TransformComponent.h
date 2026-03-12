//
// Created by Binh Nguyen Thanh on 9/3/26.
//

#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H
#include <iostream>

#include "Component.h"
#include "Vec2.h"

class TransformComponent: public Component {
public:
    using Component::Component;

    ~TransformComponent() {}

    void Update(float DeltaTime) override {
        std::cout << "TransformComponent Updated\n " << std::endl;
    }

    Vec2 GetPosition() const {
        return Position;
    }

private:
    Vec2 Position;

};

#endif //_TRANSFORMCOMPONENT_H