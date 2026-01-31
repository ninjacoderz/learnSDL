#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H
#include <SDL3/SDL.h>
#include <iostream>
#include "UserEvents.h"
#include "Button.h"

class SettingsMenu {
    public:
        void HandleEvent(SDL_Event& E) {
            if (E.type == UserEvents::OPEN_SETTINGS ||
                E.type == UserEvents::CLOSE_SETTINGS) {
                HandleUserEvent(E.user);
            }
            if(E.type == UserEvents::OPEN_SETTINGS) {
                if (E.type == UserEvents::OPEN_SETTINGS) {
                    isOpen = true;
                }
            }
        }
        void Render(SDL_Surface* Surface) const {
            // Don't render if I'm not open
            if (!isOpen) return;

            const auto* Fmt = SDL_GetPixelFormatDetails(
                Surface->format
            );

            SDL_FillSurfaceRect( 
                Surface, &Rect,
                SDL_MapRGB(
                    Fmt, nullptr,
                    Color.r, Color.g, Color.b
                )
            );
        }

    private: 
        bool isOpen { false }; 
        SDL_Rect Rect{100, 50, 200, 200};
        SDL_Color Color { 150, 150, 150, 255};
        void HandleUserEvent(SDL_UserEvent& E) {
            std::cout << "That's a user event\n";

            if (E.type == UserEvents::OPEN_SETTINGS) {
                isOpen = true;

                auto* Instigator{
                    static_cast<Button*>(E.data1)
                };
                
                std::cout << "I was opened from a button in "  << Instigator->GetLocation() << "\n";

                auto* Config{
                    static_cast<UserEvents::SettingsConfig*>(E.data1)
                };
                Rect.x = Config->x;
                Rect.y = Config->y;
                if (
                    Instigator->GetConfig().Page ==
                    UserEvents::SettingsPage::GAMEPLAY
                ) {
                    std::cout << "Page: Gameplay Settings\n";
                }
            } else if (E.type == UserEvents::CLOSE_SETTINGS) {
                isOpen = false;
            }
        }
};


#endif