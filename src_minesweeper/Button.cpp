#include "Button.h"
#include "UI.h"
#include "UserEvents.h"

void Button::OnLeftClick() {
    SDL_Event Event{ .type = isSettingsOpen
    ? UserEvents::CLOSE_SETTINGS
    : UserEvents::OPEN_SETTINGS
    };
    if (Event.type == UserEvents::OPEN_SETTINGS) {
      Event.user.data1 = this;
    }
    SDL_PushEvent(&Event);
}


void Button::HandleEvent(SDL_Event &E){
    Rectangle::HandleEvent(E);
    if (E.type == UserEvents::CLOSE_SETTINGS) {
        isSettingsOpen = false;
    } else if (E.type == UserEvents::OPEN_SETTINGS) {
        isSettingsOpen = true;
    }
}