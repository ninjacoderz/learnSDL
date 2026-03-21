//
// Created by Binh Nguyen Thanh on 7/3/26.
//

#include <iostream>
#include "Component.h"
#include "Entity.h"
#include "Scene.h"

Vec2 Component::GetOwnerPosition() const {
    TransformComponent* Transform = GetOwner()->GetComponent<TransformComponent>();
    if (!Transform) {
        std::cerr << "Entity does not have a TransformComponent!" << std::endl;
        return {0, 0};
    }
    return Transform->GetPosition();
}

void Component::SetOwnerPosition(const Vec2 &position) {
    TransformComponent* Transform = GetOwner()->GetTransformComponent();
    if (!Transform) {
        std::cerr << "Entity does not have a TransformComponent!" << std::endl;
    }
    Transform->SetPosition(position);
}

AssetManager & Component::GetAssetManager() const {
    return GetScene().GetAssetManager();
}

Scene & Component::GetScene() const {
    return GetOwner()->GetScene();
}

float Component::GetOwnerScale() const {
    TransformComponent* Transform{
        GetOwner()->GetTransformComponent()
      };
    if (!Transform) {
        std::cerr << "Error: attempted to get scale"
          " of an entity with no transform component\n";
        return 1.0;
    }
    return Transform->GetScale();
}