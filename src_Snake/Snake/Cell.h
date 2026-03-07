#pragma once
#include <SDL3/SDL.h>
#include "Globals.h"
#include "Assets.h"
#include "Snake/SnakeData.h"

enum class CellState { Snake, Apple, Empty };

class Cell {
public:
    Cell(int Row, int Column, Assets& AssetList);
    void HandleEvent(const SDL_Event& E);
    void Update(Uint64 DeltaTime);
    void Render(SDL_Surface* Surface);
    bool PlaceApple();
    void Reset();
private:
    void Advance(const SDL_UserEvent& E);
    void GrowHead(float DeltaTime);
    void ShrinkTail(float DeltaTime);

    int Row;
    int Column;
    CellState State;
    int SnakeDuration;
    SDL_Color SnakeColor;
    SDL_Rect BackgroundRect;
    SDL_Color BackgroundColor;
    Assets& AssetList;
    SDL_Rect SnakeRect;
    float FillPercent{0.0f};
    MovementDirection FillDirection{Right};
};