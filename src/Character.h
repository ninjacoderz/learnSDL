//
// Created by Binh Nguyen Thanh on 12/3/26.
//

#ifndef _CHARACTER_H
#define _CHARACTER_H
#include "Entity.h"

class Character : public Entity {
    public:
    Character() : Entity("Character") {
        Transform = AddTransformComponent();
        Image = AddImageComponent();
    }

    void SayHello () const {
        std::cout << "Character says Hello World!\n";
    }
private:
    TransformComponent* Transform = nullptr;
    ImageComponent* Image = nullptr;
};

#endif //_CHARACTER_H