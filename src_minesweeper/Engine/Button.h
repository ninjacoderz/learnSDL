#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include "Rectangle.h"
#include "Globals.h"

namespace Engine 
{
    class Button : public Rectangle
    {
   
    public:
        Button(int x, int y, int w, int h)
            : Rectangle{x, y, w, h} {
                SetColor(Config::BUTTON_COLOR);
            }
        virtual void HandleEvent ( const SDL_Event& Event) {
            if ( isDisabled ) return;
            if ( Event.type == SDL_EVENT_MOUSE_MOTION ) {
                HandleMouseMotion(Event.motion);
            } else if ( Event.type == SDL_EVENT_MOUSE_BUTTON_DOWN ){
                if (IsWithinBounds ((int)Event.button.x, (int)Event.button.y)) {
                    Event.button.button == SDL_BUTTON_LEFT ? HandleLeftClick() : HandleRightClick();
                }
            }
        }

        void SetIsDisabled(bool NewValue) {
            isDisabled = NewValue;
        }
        
    protected: 
        virtual void HandleLeftClick() {}
        virtual void HandleRightClick() {}

        virtual void HandleMouseMotion(const SDL_MouseMotionEvent& Event) {
            if ( IsWithinBounds((int) Event.x, (int) Event.y)){
                SetColor(Config::BUTTON_HOVER_COLOR);
            } else { 
                SetColor(Config::BUTTON_COLOR);
            }
        }
    private:
        bool isDisabled{false};
    };
} // namespace Engine


#endif

