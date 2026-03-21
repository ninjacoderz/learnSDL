//
// Created by Binh Nguyen Thanh on 10/3/26.
//

#include "ImageComponent.h"
#include "AssetManager.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace {
    struct BlitInfo {
        SDL_Rect SourceRect;
        SDL_Rect DestRect;
    };

    BlitInfo CalculateBlitInfo(
        ScalingMode Mode,
        // Natural surface dimensions
        int SurfaceW, int SurfaceH,
        // Target top-left screen position
        float TargetX, float TargetY,
        // Target rendering dimensions
        float TargetW, float TargetH
    ) {
        BlitInfo Info;

        // Default to rendering the whole image
        Info.SourceRect = {0, 0, SurfaceW, SurfaceH};

        // We will implement the logic for each
        // scaling mode here later...

        if (Mode == ScalingMode::None) {
            // Render at natural image size
            // and at the target position
            Info.DestRect = Utilities::Round({
              TargetX,
              TargetY,
              static_cast<float>(SurfaceW),
              static_cast<float>(SurfaceH)
            });
            return Info;
        }

        if (Mode == ScalingMode::Fill) {
            // Stretch source to fill the exact
            // target dimensions
            Info.DestRect = Utilities::Round({
              TargetX, TargetY, TargetW, TargetH
            });
            return Info;
        }

        if (Mode == ScalingMode::Contain) {
            float Scale{std::min(
              TargetW / SurfaceW,
              TargetH / SurfaceH
            )};

            Info.DestRect = Utilities::Round({
              TargetX, TargetY,
              SurfaceW * Scale,
              SurfaceH * Scale
            });

            return Info;
        }

        if (Mode == ScalingMode::Cover) {
            float Scale{std::max(
              TargetW / SurfaceW,
              TargetH / SurfaceH
            )};

            if (Scale * SurfaceW > TargetW) {
                float ClipW{TargetW / Scale};
                Info.SourceRect = Utilities::Round({
                  0, 0,
                  ClipW,
                  static_cast<float>(SurfaceH)
                });
            } else if (Scale * SurfaceH > TargetH) {
                float ClipH{TargetH / Scale};
                Info.SourceRect = Utilities::Round({
                  0, 0,
                  static_cast<float>(SurfaceW),
                  ClipH
                });
            }
            Info.DestRect = Utilities::Round({
              TargetX,
              TargetY,
              TargetW,
              TargetH
            });
            return Info;
        }

        Info.DestRect = Utilities::Round({
            TargetX, TargetY, TargetW, TargetH
        });

        return Info;
    }
}

ImageComponent::ImageComponent(Entity *owner, const std::string &FilePath) : Component(owner), ImageFilePath(FilePath) {
    ImageSurface = GetAssetManager().LoadSurface(ImageFilePath);
}

void ImageComponent::Render(SDL_Surface *Surface) {
    if (!ImageSurface) return;
    auto [TargetX, TargetY] = GetOwnerPosition() + Offset;

    float TargetW{GetWidth()};
    float TargetH{GetHeight()};

    int SurfaceW{GetSurfaceWidth()};
    int SurfaceH{GetSurfaceHeight()};

    BlitInfo Info = CalculateBlitInfo(
        ScaleMode,
        SurfaceW, SurfaceH,
        TargetX, TargetY,
        TargetW, TargetH
    );

    if (!SDL_BlitSurfaceScaled(
        ImageSurface.get(),
        &Info.SourceRect,
        Surface,
        &Info.DestRect,
        SDL_SCALEMODE_LINEAR
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
    using Utilities::DrawRectOutline;
    if (!ImageSurface) return;

    // Gather our position and dimensions for
    // the CalculateBlitInfo() function,
    // similar to what we did in Render()
    auto [TargetX, TargetY]{
        GetOwnerPosition() + Offset
    };
    float OwnerScale{GetOwnerScale()};

    float TargetW{GetWidth() * GetOwnerScale()};
    float TargetH{GetHeight() * GetOwnerScale()};

    int SurfaceW{GetSurfaceWidth()};
    int SurfaceH{GetSurfaceHeight()};

    // 1. Draw Natural Bounds (Green Outline)
    SDL_Rect NaturalBounds{
        Utilities::Round({
            TargetX, TargetY,
            SurfaceW * OwnerScale,
            SurfaceH * OwnerScale
        })
    };

    DrawRectOutline(
        Surface, NaturalBounds,
        SDL_MapRGB(
            SDL_GetPixelFormatDetails(Surface->format),
            nullptr, 0, 255, 0
        )
    );

    // 2. Draw Rendered Bounds (Red Outline)
    BlitInfo Info{
        CalculateBlitInfo(
            ScaleMode,
            SurfaceW, SurfaceH,
            TargetX, TargetY,
            TargetW, TargetH
        )
    };

    DrawRectOutline(
        Surface, Info.DestRect,
        SDL_MapRGB(
            SDL_GetPixelFormatDetails(Surface->format),
            nullptr, 255, 0, 0
        )
    );

    // Continue to draw the position
    // marker from before (Blue Square)
    SDL_Rect DebugRect{
        Utilities::Round({
            TargetX - 5, TargetY - 5, 10, 10
        })
    };

    SDL_FillSurfaceRect(
        Surface, &DebugRect,
        SDL_MapRGB(
            SDL_GetPixelFormatDetails(Surface->format),
            nullptr, 0, 0, 255
        )
    );
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

ImageComponent* ImageComponent::SetWidth(float NewWidth) {
    Width = NewWidth;
    return this;
}

ImageComponent* ImageComponent::SetHeight(int NewHeight) {
    Height = NewHeight;
    return this;
}

void ImageComponent::ResetWith() {
    Width = -0.1;
}

void ImageComponent::ResetHeight() {
    Height = -0.1;
}

float ImageComponent::GetWidth() const {
    if (Width >= 0.0f) {
        return Width;
    }
    return GetSurfaceWidth();
}

float ImageComponent::GetHeight() const {
    if (Height >= 0.0f) {
        return Height;
    }
    return GetSurfaceHeight();
}