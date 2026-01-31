#ifndef TRUNCATEDTEXT_H
#define TRUNCATEDTEXT_H

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Text.h"

class TruncatedText : public Text
{
private:
    /* data */
public:
    TruncatedText(std::string Content, float FontSize, int MaxWidth ) : Text{FontSize} {
        size_t MaxCharacters;
        TTF_MeasureString(
            Font, Content.c_str(), 0, MaxWidth, nullptr, &MaxCharacters
        );

        if(MaxCharacters < Content.size()) {
            Content.resize(MaxCharacters - 3);
            Content.append("...");
        }
        CreateSurface(Content);
    };
    
    ~TruncatedText(){};
};



#endif