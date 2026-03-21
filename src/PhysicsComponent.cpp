//
// Created by Binh Nguyen Thanh on 18/3/26.
//

#include <iostream>
#include "PhysicsComponent.h"
#include "Scene.h"
#include "Entity.h"

void PhysicsComponent::SetMass(float NewMass) {
    if (NewMass <= 0.0) {
        std::cerr << "Error: Mass must be positive. "
                     "Setting to 1.0kg instead.\n";
        Mass = 1.0;
    } else {
        Mass = NewMass;
    }
}

void PhysicsComponent::ApplyForce(const Vec2& Force) {
    // A = F/M
    if (Mass > 0.0f) { // Avoid division by zero
        Acceleration += Force / Mass;
    }
}

void PhysicsComponent::ApplyImpulse(
  const Vec2& Impulse
) {
    // Change in Velocity = Impulse / Mass
    if (Mass > 0.0f) { // Avoid division by zero
        Velocity += Impulse / Mass;
    }
}

void PhysicsComponent::Update(float DeltaTime) {
    ApplyForce(GetScene().GRAVITY * Mass);
    Velocity += Acceleration * DeltaTime;
    SetOwnerPosition(
      GetOwnerPosition() + Velocity * DeltaTime
    );
    Acceleration = {0.0, 0.0};

    // Reset horizontal velocity for every frame
    Velocity.x = 0;
}

void PhysicsComponent::Initialize() {
    // Physics needs a Transform to know where
    // the entity is
    if (!GetOwner()->GetTransformComponent()) {
        std::cerr << "Error: PhysicsComponent "
          "requires TransformComponent on its Owner.\n";

        // Request self-removal
        GetOwner()->RemoveComponent(this);
    }
}

void PhysicsComponent::DrawDebugHelpers(SDL_Surface *Surface) {
#ifdef DRAW_DEBUG_HELPERS
    auto [x, y]{GetOwnerPosition()};
    SDL_Rect PositionIndicator{
        int(x) - 2, int(y) - 2, 4, 4
      };
    SDL_FillSurfaceRect(
      GetScene().Trajectories,
      &PositionIndicator,
      SDL_MapRGB(
        SDL_GetPixelFormatDetails(
          GetScene().Trajectories->format
        ),
        nullptr, 0, 0, 255
      )
    );
#endif
}
