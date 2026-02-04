#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include "Rectangle.h"
#include "UserEvents.h"

class UI;

class Button: public Rectangle {
    public:
    Button(const SDL_Rect& Rect)
    : Rectangle{Rect}
    {
        SetColor({255, 165, 0, 255});
    }


    void onMouseEnter() override {
        std::cout << "Hello mouse\n";
    }

    void OnMouseExit() override {
        std::cout << "Goodbye mouse\n";
    }

    void OnLeftClick() override ;

    void HandleEvent(SDL_Event& E);


    UserEvents::SettingsConfig GetConfig() {
        return Config;
    }

    std::string GetLocation() {
        return "the main menu";
    }
    private:
        bool isSettingsOpen{false};

        UserEvents::SettingsConfig Config{
            UserEvents::SettingsPage::GAMEPLAY,
            50, 100
        };

};

#endif
