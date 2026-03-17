//
// Created by Binh Nguyen Thanh on 10/3/26.
//

#include "ImageComponent.h"
#include "AssetManager.h"
#include "Entity.h"
#include "TransformComponent.h"

ImageComponent::ImageComponent(Entity *owner, const std::string &FilePath):
    Component(owner), ImageFilePath(FilePath) {
        ImageSurface = GetAssetManager().LoadSurface(ImageFilePath);
}

void ImageComponent::Render(SDL_Surface *Surface) {
    if (!ImageSurface) return;
    auto [x, y] = GetOwnerPosition() + Offset;
    SDL_Rect Destination =
        Utilities::Round({x, y, 0, 0});
    if (!SDL_BlitSurface(
      ImageSurface.get(),
      nullptr,
      Surface,
      &Destination
    )) {
        std::cerr << "Error: Blit failed: "
          << SDL_GetError() << '\n';
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

auto ImageComponent::DrawDebugHelpers(SDL_Surface *Surface) -> void {
    if (!ImageSurface) return;

    auto [x, y]{GetOwnerPosition() + Offset};

    SDL_Rect DebugRect{Utilities::Round({
        x - 5, y - 5, 10, 10 })};

    SDL_FillSurfaceRect(Surface, &DebugRect, SDL_MapRGB(
      SDL_GetPixelFormatDetails(Surface->format),
      nullptr, 0, 0, 255));
}

bool ImageComponent::LoadNewImage(const std::string &NewPath) {
    // Store the new file path
    ImageFilePath = NewPath;

    // Use our asset manager
    ImageSurface = GetAssetManager()
      .LoadSurface(NewPath);

    // Return true if the load was
    // successful (surface is not null)
    return ImageSurface != nullptr;
}

int ImageComponent::GetSurfaceWidth() const {
    if (!ImageSurface) {
        std::cerr << "Warning: Attempted to get "
          "width from null ImageSurface.\n";
        return 0;
    }
    return ImageSurface->w;
}

int ImageComponent::GetSurfaceHeight() const {
    if (!ImageSurface) {
        std::cerr << "Warning: Attempted to get "
          "height from null ImageSurface.\n";
        return 0;
    }
    return ImageSurface->h;
}
