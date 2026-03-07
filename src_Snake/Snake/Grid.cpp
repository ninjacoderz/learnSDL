//
// Created by Binh Nguyen Thanh on 28/2/26.
//

#include "Grid.h"
#include "Engine/Random.h"

using namespace Config;

Grid::Grid(Assets &AssetList) {
    Cells.reserve(GRID_ROWS * GRID_COLUMNS);
    for (int i = 0; i < GRID_ROWS ; i++) {
        for (int j = 0; j < GRID_COLUMNS; j++) {
            Cells.emplace_back(i, j, AssetList);
        }
    }
}

void Grid::HandleEvents(const SDL_Event &event) {
    for (auto& Cell : Cells) {
        Cell.HandleEvent(event);
    }

    if (event.type == UserEvents::APPLE_EATEN) {
        PlaceRandomApple();
    }
}

void Grid::Update(Uint64 DeltaTime) {
    for (auto& Cell : Cells) {
        Cell.Update(DeltaTime);
    }
}

void Grid::Render(SDL_Surface *Surface) {
    for (auto& Cell : Cells) {
        Cell.Render(Surface);
    }
}

void Grid::PlaceRandomApple() {
    while (true) {
        const int RandNums = Engine::Random::Int(0, Cells.size() - 1);
        if ( Cells[RandNums].PlaceApple() ) break;
    }
}
