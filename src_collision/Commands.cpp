//
// Created by Binh Nguyen Thanh on 12/3/26.
//

#include "Commands.h"
#include "Entity.h"
#include <iostream>
#include "PhysicsComponent.h"
void MovementCommand::Execute(Entity *Target) {
    PhysicsComponent* Physics{
        Target->GetPhysicsComponent()
      };
    if (Physics) {
        Physics->SetVelocity({
          Velocity.x,
          Physics->GetVelocity().y
        });
    } else {
        std::cerr << "Error: MovementCommand "
          "requires a PhysicsComponent on entity\n";
    }
}

void MovementCommand::Undo() {
    Target->GetTransformComponent()->Move(-Movement);
}


void JumpCommand::Execute(Entity* Target) {
    if (!Target) return;  // Safety Check
    PhysicsComponent* Physics{
        Target->GetPhysicsComponent()
      };
    if (Physics) {
        Physics->ApplyImpulse(Impulse);
    } else {
        std::cerr << "Error: JumpCommand "
          "requires a PhysicsComponent on entity\n";
    }
}
