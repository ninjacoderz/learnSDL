//
// Created by Binh Nguyen Thanh on 12/3/26.
//

#ifndef _COMMANDS_H
#define _COMMANDS_H
#pragma once
#include "Vec2.h"
class Entity;
class Command {
    public:
    virtual ~Command() = default;
    virtual void Execute(Entity* Target){}
};


class MovementCommand : public Command {
public:
    MovementCommand(Vec2 Movement): Movement(Movement) {}
    void Execute(Entity* Target) override;
    void Undo();
private:
    Entity* Target;
    Vec2 Movement;
};

#endif //_COMMANDS_H