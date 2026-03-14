//
// Created by Binh Nguyen Thanh on 12/3/26.
//

#include "Commands.h"
#include "Entity.h"
void MovementCommand::Execute(Entity *Target) {
    Command::Execute(Target);
    this->Target = Target;
    Target->GetTransformComponent()->Move(Movement);
}

void MovementCommand::Undo() {
    Target->GetTransformComponent()->Move(-Movement);
}
