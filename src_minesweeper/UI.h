#ifndef UI_H
#define UI_H

#include <vector>
#include <SDL3/SDL.h>

#include "Rectangle.h"

#include "Header.h"
#include "Footer.h"
#include "Grid.h"

#include "Button.h"
#include "SettingsMenu.h"

class UI {
    public: 
        UI() {
        }

        void render(SDL_Surface* surface) const {
            SettingsButton.Render(surface);
            SettingsMenu.Render(surface);
        }

        void handleEvent(SDL_Event& E) {
            SettingsButton.HandleEvent(E);
            SettingsMenu.HandleEvent(E);
        }
    
    private:
        Button SettingsButton{{50, 50, 50, 50}};
        SettingsMenu SettingsMenu;
};

#endif