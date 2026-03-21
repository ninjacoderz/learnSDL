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
    void Execute(Entity* Target) override;
    void Undo();

    MovementCommand(Vec2 Velocity)
        : Velocity(Velocity) {}
private:
    Entity* Target;
    Vec2 Movement;
    Vec2 Velocity;
};

class JumpCommand : public Command {
public:
    JumpCommand(Vec2 Impulse)
        : Impulse(Impulse) {}
    void Execute(Entity* Target) override;
    Vec2 Impulse;
};

#endif //_COMMANDS_H