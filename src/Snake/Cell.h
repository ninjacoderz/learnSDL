//
// Created by Binh Nguyen Thanh on 28/2/26.
//

#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H
#include "Assets.h"
#include "Globals.h"

enum class CellState { Snake, Apple, Empty };

class Cell {
public:
    Cell(int Row, int Col, Assets& AssetList);
    void HandleEvent(const SDL_Event& e);
    void Render(SDL_Surface* renderer);
    void Update(Uint64 DeltaTime);
    void Initialize();

    void Advance(const SDL_UserEvent& E);

    bool PlaceApple();

private:
    int Row;
    int Column;
    Assets& AssetList;
    SDL_Rect BackgroundRect;
    SDL_Color BackgroundColor;
    CellState State;
    int SnakeDuration = 0;
};


#endif //MINESWEEPER_CELL_H