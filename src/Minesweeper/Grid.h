#ifndef GRID_H
#define GRID_H

#include <vector>
#include <SDL3/SDL.h>
#include "Globals.h"
#include "Minesweeper/Cell.h"
#include "../Engine/Random.h"

using namespace Engine;
using namespace Config;

class MinesweeperGrid
{

public:
    MinesweeperGrid(int x, int y) {
        Children.reserve(GRID_COLUMNS * GRID_ROWS);
        for ( int Col = 0;  Col < GRID_COLUMNS ; Col++ ) {
            for ( int Row = 0; Row < GRID_ROWS; Row ++ ) {
                constexpr int Spacing{CELL_SIZE + PADDING};
                // Consider
                Children.emplace_back(
                    x + Spacing * (Col), y + Spacing * (Row),
                    CELL_SIZE, CELL_SIZE, 
                    Row, Col
                );
            }
        }
        PlaceBombs();
    };

    void Render(SDL_Surface* Surface) {
        for(auto& Child: Children) {
            Child.Render(Surface);
        }
    }

    void HandleEvent(const SDL_Event& Event){
        if (Event.type == UserEvents::CELL_CLEARED) {
            HandleCellCleared(Event.user);
        } else if (Event.type == UserEvents::NEW_GAME) {
            for (auto& Child : Children) {
                Child.Reset();
            }
            PlaceBombs();
        }

        for(auto& Child: Children){
            Child.HandleEvent(Event);
        }
    }

    ~MinesweeperGrid() {};

private:
    void HandleCellCleared( const SDL_UserEvent& Event) {
        auto* cell = static_cast<MinesweeperCell*> (Event.data1);

        if(cell->GetHasBomb()) {
            SDL_Event Event{};
            Event.type = UserEvents::GAME_LOST;
            SDL_PushEvent(&Event);
        } else {
            --CellsToClear;
            if(CellsToClear == 0) {
                SDL_Event Event{};
                Event.type = UserEvents::GAME_WON;
                SDL_PushEvent(&Event);
            }
        }
    }
    void PlaceBombs(){
        int BombsToPlace{Config::BOMB_COUNT};
        CellsToClear = Config::GRID_COLUMNS *
            Config::GRID_ROWS - Config::BOMB_COUNT;
        while (BombsToPlace > 0 )   
        {
            const size_t RandomIndex{ Random::Int(0, Children.size() - 1) };
            if(Children[RandomIndex].PlaceBomb()) {
                --BombsToPlace;
            }

        }
        
    }
    int CellsToClear{0};
    std::vector<MinesweeperCell> Children; 
};

#endif