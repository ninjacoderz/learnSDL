#include <iostream>
#include <SDL3/SDL.h>
#include "Minesweeper/Cell.h"
#include "Globals.h"
#include "Cell.h"
#include <memory>
#include <string>

MinesweeperCell::MinesweeperCell(int X, int Y, int W, int H, int Row, int Col) 
: Button{X, Y, W, H}, Row{Row}, Col{Col}
{
    BombImage = std::make_unique<Image>(
        X, Y, W, H,
        Config::BOMB_IMAGE
    );

    FlagImage = std::make_unique<Engine::Image>(
        X, Y, W, H,
        Config::FLAG_IMAGE
    );

    Text = std::make_unique<Engine::Text>(
        X, Y, W, H,
        std::to_string(AdjacentBombs),
        Config::TEXT_COLORS[AdjacentBombs]
    );
};

void MinesweeperCell::HandleEvent(const SDL_Event &Event)
{
    if(Event.type == UserEvents::CELL_CLEARED){
        std::cout << "A Cell Was Cleared\n";
        HandleCellCleared(Event.user);
    } else if (Event.type == UserEvents::BOMB_PLACED) {
        // TODO
        std::cout << "A Bomb was Placed\n";
        HandleBombPlaced(Event.user);
    } else if (Event.type == UserEvents::GAME_WON) {
        if (hasBomb) {
            hasFlag = true; 
            SetColor(Config::BUTTON_SUCCESS_COLOR);
        }
        SetIsDisabled(true);
    } else if (Event.type == UserEvents::GAME_LOST) {
        if (hasBomb) {
            isCleared = true;
            SetColor(Config::BUTTON_FAILURE_COLOR);
        }
        SetIsDisabled(true);
    }
    Button::HandleEvent(Event);
}

void MinesweeperCell::Render(SDL_Surface *Surface)
{
    Button::Render(Surface);
    if (hasFlag) {
        FlagImage->Render(Surface);
    } else if (isCleared && hasBomb) {
        BombImage->Render(Surface);
    } else if (isCleared && AdjacentBombs > 0) {
        Text->Render(Surface);
    }
}
bool MinesweeperCell::PlaceBomb()
{
    if(hasBomb) return false;
    hasBomb = true;
    ReportEvent(UserEvents::BOMB_PLACED);
    return true;
}
bool MinesweeperCell::isAdjacent(const MinesweeperCell *Other) const
{
    return !(Other == this) && std::abs(GetRow() - Other->GetRow()) <= 1 
        && std::abs(GetCol() - Other->GetCol()) <= 1 ;
}
void MinesweeperCell::ReportEvent(Uint32 EventType)
{
    SDL_Event event{};
    event.type = EventType;
    event.user.data1 = this;
    SDL_PushEvent(&event);
}
void MinesweeperCell::ClearCell()
{
    if (isCleared) return;
    isCleared = true;
    SetIsDisabled(true);
    SetColor(Config::BUTTON_CLEARED_COLOR);
    ReportEvent(UserEvents::CELL_CLEARED);
}

void MinesweeperCell::Reset(){
  isCleared = false;
  hasBomb = false;
  hasFlag = false;
  AdjacentBombs = 0;
  SetIsDisabled(false);
  SetColor(Config::BUTTON_COLOR);
  Text->SetText(
    std::to_string(AdjacentBombs),
    Config::TEXT_COLORS[AdjacentBombs]
  );
}

void MinesweeperCell::HandleLeftClick()
{
    if(!hasFlag)   ClearCell();
}

void MinesweeperCell::HandleRightClick()
{
    if(hasFlag) {
        ReportEvent(UserEvents::FLAG_CLEARED);
        hasFlag = false;
    } else {
        ReportEvent(UserEvents::FLAG_PLACED);
        hasFlag = true;
    }
}

void MinesweeperCell::HandleBombPlaced(const SDL_UserEvent &Event)
{
    const MinesweeperCell* cell = static_cast<MinesweeperCell*> (Event.data1);
    if(isAdjacent(cell))
        ++AdjacentBombs;
    Text->SetText(
        std::to_string(AdjacentBombs),
        Config::TEXT_COLORS[AdjacentBombs]
    );
}

void MinesweeperCell::HandleCellCleared(const SDL_UserEvent& Event)
{
    const MinesweeperCell* cell = static_cast<MinesweeperCell*>(Event.data1);
    if(cell->GetHasBomb()) return;
    if(isAdjacent(cell) && cell->AdjacentBombs == 0) {
        ClearCell();
    }
}
