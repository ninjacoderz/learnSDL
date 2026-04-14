//
// Created by Binh Nguyen Thanh on 26/3/26.
//

#include <SDL3/SDL.h>
#include "GameObject.h"

void GameObject::Render(SDL_Surface* Surface) {
    Image.Render(Surface, Position);
}