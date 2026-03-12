//
// Created by Binh Nguyen Thanh on 10/3/26.
//

#include "ImageComponent.h"

#include "Entity.h"
#include "TransformComponent.h"

void ImageComponent::Render(SDL_Surface *Surface) {
    TransformComponent *Transform = GetOwner()->GetTransformComponent();
    std::cout << "ImageComponent rendering at: " << Transform->GetPosition() << std::endl;
}

void ImageComponent::Initialize() {
    Component::Initialize();
    Entity *Owner = GetOwner();
    if (!Owner->GetComponent<TransformComponent>()) {
        std::cout << "Error: ImageComponent "
                "requires TransformComponent on its Owner\n";

        // Request removal
        Owner->RemoveComponent(this);
    }
}

void ImageComponent::OnComponentRemoved(Component * Component) {
    if (dynamic_cast<TransformComponent*>(Component)) {
        std::cout << "ImageComponent: Owner's "
          "TransformComponent was removed!\n";

        // React to removal...
    }
}
