#pragma once
#include "Game.h"
#include "MapActor.h"
#include "InputSystem.h"

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
    InputSystem* mInputSystem;
    bool mIsRunning;
    // mPlayer sẽ thêm sau khi có ISOActor
};