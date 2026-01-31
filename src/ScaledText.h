#ifndef SCALEDTEXT_H
#define SCALEDTEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Text.h"

class ScaledText : public Text {
 public:
 
  ScaledText(
    const std::string& Content, int TargetWidth)
    : Text{BaseFontSize} {
    int Width;
    TTF_Text* TempText = TTF_CreateText(
      nullptr, Font, Content.c_str(), 0
    );
    TTF_GetTextSize(
      TempText,
      &Width, nullptr
    );
    TTF_DestroyText(TempText);

    float Ratio{static_cast<float>(
      TargetWidth
    ) / Width};

    SetFontSize(BaseFontSize * Ratio);
    CreateSurface(Content);
  }
private:
  static constexpr float BaseFontSize{24.0f};
};

#endif