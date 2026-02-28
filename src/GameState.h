#pragma once

#include "SDL3/SDL.h"
#include "Globals.h"
#include "Snake/SnakeData.h"

class GameState {
public:
    void HandleEvents(SDL_Event &E) {
        if (E.type == SDL_EVENT_KEY_DOWN) {
            HandleKeyEvent(E.key);
        }
    };
    void Update(Uint32 DeltaTime) {
        ElapsedTime += DeltaTime;
        if (ElapsedTime >= Config::ADVANCE_INTERVAL) {
            ElapsedTime = 0;
            UpdateSnake();
        }
    };
private:

    void HandleKeyEvent(const SDL_KeyboardEvent& E) {
        switch (E.key) {
            case SDLK_UP:
            case SDLK_W:
                if (Snake.Direction != Down) {
                    NextDirection = Up;
                }
                break;
            case SDLK_DOWN:
            case SDLK_S:
                if (Snake.Direction != Up) {
                    NextDirection = Down;
                }
                break;
            case SDLK_LEFT:
            case SDLK_A:
                if (Snake.Direction != Right) {
                    NextDirection = Left;
                }
                break;
            case SDLK_RIGHT:
            case SDLK_D:
                if (Snake.Direction != Left) {
                    NextDirection = Right;
                }
                break;
        }
    }

    void UpdateSnake() {
        Snake.Direction = NextDirection;
        switch (NextDirection) {
            case Up:
                Snake.HeadRow--;
                break;
            case Down:
                Snake.HeadRow++;
                break;
            case Left:
                Snake.HeadCol--;
                break;
            case Right:
                Snake.HeadCol++;
                break;
        }
        SDL_Event Event{};
        Event.type = UserEvents::ADVANCE;
        Event.user.data1 = &Snake;
        SDL_PushEvent(&Event);
    }
    SnakeData Snake = SnakeData(
        Config::GRID_ROWS / 2, 3, 2, Right);
    Uint64 ElapsedTime{0};

    MovementDirection NextDirection = Right;

};