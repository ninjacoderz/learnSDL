//
// Created by Binh Nguyen Thanh on 9/3/26.
//

#ifndef _IMAGECOMPONENT_H
#define _IMAGECOMPONENT_H
#include <string>
#include <SDL3/SDL.h>
#include "Component.h"

class ImageComponent : public Component {
public:
    using Component::Component;
    ImageComponent(Entity* owner, const std::string& FilePath);
    ~ImageComponent() override;
    void Render(SDL_Surface* Surface) override;
    void Initialize() override;
private:
    SDL_Surface *ImageSurface  = nullptr;
    std::string ImageFilePath;
};

#endif //_IMAGECOMPONENT_H
