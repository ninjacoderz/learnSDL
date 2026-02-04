#ifndef ROW_H
#define ROW_H

#include <string>
#include <SDL3/SDL.h>
#include "Globals.h"
#include "Rectangle.h"

using namespace Engine;

class Row : public Rectangle
{

public:
    Row(int x, int y, int w, int h, std::vector<Rectangle> Children)
        :Children{Children}, Rectangle(x, y, w, h) {

    };

    void Render(SDL_Surface* Surface){
        for(Rectangle Child: Children) {
            Child.Render(Surface);
        }
    }

    ~Row() {};

private:
    std::vector<Rectangle> Children;
};



#endif