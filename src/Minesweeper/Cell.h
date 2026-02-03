#ifndef CELL_H
#define CELL_H

#include <SDL3/SDL.h>
#include "Engine/Button.h"
#include "Engine/Image.h"
#include "Engine/Text.h"

using namespace Engine;

class MinesweeperCell: public Button
{
public:
    MinesweeperCell(int X, int Y, int W, int H, int Row, int Col );
    void HandleEvent(const SDL_Event& Event) override;
    void Render(SDL_Surface* Surface) override;
    bool PlaceBomb();

    [[nodiscard]]
    bool GetHasBomb() const{ return hasBomb; }

    [[nodiscard]]
    int GetRow() const{ return Row; }

    [[nodiscard]]
    int GetCol() const{ return Col; }
    
    void Reset();
protected: 
    void HandleLeftClick() override;
    void HandleRightClick() override;
private:
    void HandleBombPlaced ( const SDL_UserEvent& Event );
    void HandleCellCleared(const SDL_UserEvent& Event);
    int AdjacentBombs{0};
    bool isAdjacent(const MinesweeperCell* Other) const;
    void ReportEvent(Uint32 EventType);
    void ClearCell();
    bool isCleared{false};
    int Row;
    int Col;
    bool hasBomb {false};
    std::unique_ptr<Image> BombImage;
    std::unique_ptr<Engine::Text> Text;
    std::unique_ptr<Engine::Image> FlagImage;
    bool hasFlag{false};
};

#endif