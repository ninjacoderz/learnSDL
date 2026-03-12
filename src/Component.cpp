//
// Created by Binh Nguyen Thanh on 7/3/26.
//

#include <iostream>
#include "Component.h"
#include "Entity.h"

void AnimationComponent::Update(float DeltaTime) {
    std::cout << Owner->GetName() << ": Animating\n";
}

void AudioComponent::Update(float DeltaTime) {
    std::cout << Owner->GetName() << ": Audio\n";
}

void PhysicsComponent::Update(float DeltaTime) {
    std::cout << Owner->GetName() << ": Physics\n";
}