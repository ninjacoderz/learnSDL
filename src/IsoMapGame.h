#pragma once
#include "Game.h"
#include "MapActor.h"

class IsoMapGame : public Game {
public:
    IsoMapGame(SDL_Window* window, SDL_Renderer* renderer);

    void LoadData()   override;
    void UnloadData() ;
    void ProcessInput() override;
    void GenerateOutput() override;
    void Initialize(SDL_Window* window, SDL_Renderer* renderer) ;

private:
    MapActor* mMapActor = nullptr;
    // mPlayer sẽ thêm sau khi có ISOActor
};