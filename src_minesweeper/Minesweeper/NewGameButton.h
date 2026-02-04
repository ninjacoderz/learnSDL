
#ifndef NEWGAMEBUTTON_H
#define NEWGAMEBUTTON_H

#include "Engine/Button.h"
#include "Engine/Text.h"

using namespace Engine;

class NewGameButton : public Button
{
public:
    NewGameButton(int x, int y, int w, int h) : Button {x,y,w,h}, Text{x,y,w,h, "New Game", {}, 20.0f} {}
    
    void Render(SDL_Surface* Surface) override {
        Button::Render(Surface);
        Text.Render(Surface);
    }

    ~NewGameButton(){};

protected: 
    void HandleLeftClick() override {
        SDL_Event Event{};
        Event.type = UserEvents::NEW_GAME;
        SDL_PushEvent(&Event);
    }
private:
    Text Text;
};


#endif