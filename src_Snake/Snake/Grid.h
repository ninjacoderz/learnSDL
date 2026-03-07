//
// Created by Binh Nguyen Thanh on 28/2/26.
//

#ifndef MINESWEEPER_GRID_H
#define MINESWEEPER_GRID_H

#include <vector>

#include "Cell.h"
#include "Globals.h"

class Grid {
public:
    Grid(Assets& AssetList);
    ~Grid(){};
    void HandleEvents(const SDL_Event& event);
    void Update(Uint64 DeltaTime);
    void Render(SDL_Surface* Surface);

    void PlaceRandomApple();

private:
    std::vector<Cell> Cells;
};


#endif //MINESWEEPER_GRID_H