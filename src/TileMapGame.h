#pragma once
#include <string>
#include "Game.h"
#include "SpriteSheetActor.h"

class TileMapGame: public Game
{
    public: 
        TileMapGame(SDL_Window* window, SDL_Renderer* renderer);
        void LoadData() override;
        void UnloadData(); 
        void ProcessInput() override;
        void Initialize(SDL_Window* _window, SDL_Renderer* _renderer);

       private: 
        SpriteSheetActor* player;
        Actor* tileActor;
        const bool* mCurrKeyboardState;
};