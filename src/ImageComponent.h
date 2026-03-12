//
// Created by Binh Nguyen Thanh on 9/3/26.
//

#ifndef _IMAGECOMPONENT_H
#define _IMAGECOMPONENT_H

#include "Component.h"

class ImageComponent : public Component {
public:
    using Component::Component;
    void Render(SDL_Surface* Surface) override;
    void Initialize() override;
    void OnComponentRemoved(Component*);
};

#endif //_IMAGECOMPONENT_H
