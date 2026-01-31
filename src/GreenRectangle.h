#ifndef GREENRECTANGLE_H
#define GREENRECTANGLE_H

#include "Rectangle.h"

class GreenRectangle: public Rectangle
{
private:
    
public:
    GreenRectangle(const SDL_Rect& Rect);
    ~GreenRectangle();
};

GreenRectangle::GreenRectangle(const SDL_Rect& rect) : Rectangle(rect)
{
    SetColor({0,255,0,255});
}

inline GreenRectangle::~GreenRectangle()
{
}

#endif