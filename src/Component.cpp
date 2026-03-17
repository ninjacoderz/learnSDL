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

AssetManager & Component::GetAssetManager() const {
    return GetScene().GetAssetManager();
}

Scene & Component::GetScene() const {
    return GetOwner()->GetScene();
}
