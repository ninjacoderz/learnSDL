#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL3/SDL.h>
#include <iostream>

class Rectangle {
    public:
    Rectangle( const SDL_Rect& rect);

    virtual ~Rectangle() = default;

    virtual void Render(SDL_Surface* surface) const;
    virtual void onMouseEnter(){}; 
    virtual void OnMouseExit() {}
    virtual void OnLeftClick() {}

    void HandleEvent(SDL_Event& E) {
        if (E.type == SDL_EVENT_MOUSE_MOTION) {
            bool wasPointerHovering{isPointerHovering};
            isPointerHovering = isWithinRect(
                (int)E.motion.x, (int)E.motion.y
            );
            if (!wasPointerHovering && isPointerHovering) {
                onMouseEnter();
            } else if (
                wasPointerHovering && !isPointerHovering
            ) {
                OnMouseExit();
            }
        } else if (E.type == SDL_EVENT_WINDOW_MOUSE_LEAVE) {
            isPointerHovering = false;
            OnMouseExit();
        } else if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (isPointerHovering &&
                E.button.button == SDL_BUTTON_LEFT
            ) {
                std::cout << "A left-click happened "
                "on me!\n";
                OnLeftClick();
            }
        }
    }

    void SetColor(const SDL_Color& NewColor) {
        color = NewColor;
    }

    SDL_Color GetColor() const {
        return color;
    }

    void SetHoverColor(const SDL_Color& NewColor) {
        hoverColor = NewColor;
    }

    private:
    SDL_Rect rect;
    SDL_Color color{255, 0, 0, 255};
    SDL_Color hoverColor{0, 0, 255, 255};
    
    protected:
    bool isPointerHovering{false};

    

    
    bool isWithinRect(int x, int y) {
        if (x < rect.x) return false;
        if (x > rect.x + rect.w) return false;
        if (y < rect.y) return false;
        if (y > rect.y + rect.h) return false;
        return true;
    }
};

#endif