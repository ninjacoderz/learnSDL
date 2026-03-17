//
// Created by Binh Nguyen Thanh on 9/3/26.
//

#ifndef _IMAGECOMPONENT_H
#define _IMAGECOMPONENT_H
#include <string>
#include <SDL3/SDL.h>

#include "AssetManager.h"
#include "Component.h"

class ImageComponent : public Component {
public:
    using Component::Component;
    ImageComponent(Entity* owner, const std::string& FilePath);
    void Render(SDL_Surface* Surface) override;
    void Initialize() override;
    void DrawDebugHelpers(SDL_Surface*) override;
    bool LoadNewImage(const std::string& NewPath);

    void SetOffset(const Vec2& NewOffset) {
        Offset = NewOffset;
    }

    int GetSurfaceWidth() const;
    int GetSurfaceHeight() const;
private:
    std::shared_ptr<SDL_Surface> ImageSurface = nullptr;
    std::string ImageFilePath;
    Vec2 Offset= {0, 0};
};

#endif //_IMAGECOMPONENT_H
