//
// Created by Binh Nguyen Thanh on 1/3/26.
//

#ifndef MINESWEEPER_RESTARTBUTTON_H
#define MINESWEEPER_RESTARTBUTTON_H
#include "Engine/Text.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_surface.h"

class RestartButton {
public:
    RestartButton(int x, int y, int width, int height)
        : ButtonRect(x, y, width, height),
          CurrentColor(Config::BUTTON_COLOR),
          Text("RESTART", 20),
        TextRect{
            x + Config::PADDING * 5,
            y + Config::PADDING * 3,
            0, 0
          }{
    };

    void Render(SDL_Surface *Surface) {
        SDL_FillSurfaceRect(Surface, &ButtonRect, SDL_MapRGB(
                                SDL_GetPixelFormatDetails(Surface->format),
                                nullptr,
                                CurrentColor.r,
                                CurrentColor.g,
                                CurrentColor.b
                            ));
        Text.Render(Surface, &TextRect);
    };

    void HandleEvents(const SDL_Event &Event) {
        if (Event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            HandleClick(Event.button);
        } else if (
          Event.type == UserEvents::GAME_LOST ||
          Event.type == UserEvents::GAME_WON
        ) {
            CurrentColor = Config::BUTTON_HIGHLIGHT_COLOR;
        } else if (Event.type == UserEvents::RESTART_GAME) {
            CurrentColor = Config::BUTTON_COLOR;
        }
    };

private:
    Engine::Text Text;
    SDL_Rect TextRect;
    SDL_Rect ButtonRect;
    SDL_Color CurrentColor;
    void HandleClick(const SDL_MouseButtonEvent &event) {
        if (
            event.x >= ButtonRect.x &&
            event.x <= ButtonRect.x + ButtonRect.w &&
            event.y >= ButtonRect.y &&
            event.y <= ButtonRect.y + ButtonRect.h
        ) {
            SDL_Event RestartEvent{
                .type = UserEvents::RESTART_GAME
            };
            SDL_PushEvent(&RestartEvent);
        }
    };
};

#endif //MINESWEEPER_RESTARTBUTTON_H
