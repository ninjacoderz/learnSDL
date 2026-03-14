//
// Created by Binh Nguyen Thanh on 10/3/26.
//

#include "ImageComponent.h"

#include "Entity.h"
#include "TransformComponent.h"
#include <SDL3_image/SDL_image.h>

ImageComponent::ImageComponent(Entity *owner, const std::string &FilePath): Component(owner), ImageFilePath(FilePath) {
    ImageSurface = IMG_Load(FilePath.c_str());
    if (ImageSurface == nullptr) {
        std::cerr << "Failed to load image: " << FilePath << " Error: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "Loaded image: " << FilePath << std::endl;
    }
}

ImageComponent::~ImageComponent() {
    SDL_DestroySurface(ImageSurface);
    // Set pointer to null after freeing to be safe
    ImageSurface = nullptr;
}

void ImageComponent::Render(SDL_Surface *Surface) {
    if (!ImageSurface) return;
    TransformComponent* Transform{
        GetOwner()->GetTransformComponent()};
    if (Transform) {
        // Just print a message for now
        std::cout << "ImageComponent ("
          << ImageFilePath
          << ") ready to render at: "
          << Transform->GetPosition() << '\n';
    } else {
        // Handle case where transform is missing
        std::cout << "ImageComponent ("
          << ImageFilePath
          << ") ready, but no TransformComponent found\n";
    }
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