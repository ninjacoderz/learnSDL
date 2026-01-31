#include "Rectangle.h"

Rectangle::Rectangle(const SDL_Rect &rect): rect(rect)
{
}

void Rectangle::Render(SDL_Surface *surface) const
{
    auto [r, g, b, a]{
      isPointerHovering ? hoverColor : color
    };

    const auto* fmt = SDL_GetPixelFormatDetails(
      surface->format
    );

    SDL_FillSurfaceRect(
      surface, &rect,
      SDL_MapRGB(fmt, nullptr, r, g, b)
    );
}
