#ifndef FLAGCOUNTER_H
#define FLAGCOUNTER_H

#include <string>
#include <memory>
#include <SDL3/SDL.h>

#include "Globals.h"
#include "Engine/Rectangle.h"
#include "Engine/Text.h"
#include "Engine/Image.h"
using namespace Engine;

class FlagCounter : public Rectangle
{
public:
    FlagCounter(int x, int y, int w, int h) : 
        Rectangle{x,y,w,h, Config::FLAG_COUNTER_COLOR}, 
        Image{
            std::make_unique<Engine::Image>(
            x, y,
            Config::FOOTER_HEIGHT - Config::PADDING,
            Config::FOOTER_HEIGHT - Config::PADDING,
            Config::FLAG_IMAGE,
            24
            )},
        Text{
            std::make_unique<Engine::Text>(
                x + Config::FOOTER_HEIGHT, y,
                w - Config::FOOTER_HEIGHT - 24, h,
                std::to_string(Config::BOMB_COUNT),
                SDL_Color{255, 255, 255, 255}, 20.0f
            )}{}
    
    void Render(SDL_Surface* Surface) override {
        Rectangle::Render(Surface);
        Text->Render(Surface);
        Image->Render(Surface);
    }

    void HandleEvent(const SDL_Event& E){
        if (E.type == UserEvents::FLAG_PLACED) {
            --FlagsAvailable;
        } else if (E.type == UserEvents::FLAG_CLEARED) {
            ++FlagsAvailable;
        } else if (E.type == UserEvents::GAME_WON) {
            FlagsAvailable = 0;
        } else if (E.type == UserEvents::NEW_GAME) {
            FlagsAvailable = Config::BOMB_COUNT;
        } else { 
            return; 
        }

        Text->SetText(
            std::to_string(FlagsAvailable)
        );
    }

private:
    std::unique_ptr<Engine::Image> Image;
    std::unique_ptr<Engine::Text> Text;
    int FlagsAvailable{Config::BOMB_COUNT};
};


#endif