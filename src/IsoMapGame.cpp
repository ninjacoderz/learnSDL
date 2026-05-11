#include "IsoMapGame.h"
#include "SpriteComponent.h"
#include "ISORenderer.h"
#include "Defs.h"

IsoMapGame::IsoMapGame(SDL_Window* window, SDL_Renderer* renderer) {
    Initialize(window, renderer);
    LoadData();
}

void IsoMapGame::LoadData() {
    auto& iso   = ISORenderer::Get();

    // Port trực tiếp từ Defs.h C cũ
    iso.tileW   = TILE_WIDTH;           // 60
    iso.tileH   = TILE_HEIGHT;          // 30
    iso.originX = MAP_RENDER_OFFSET_X;  // 80
    iso.originY = MAP_RENDER_OFFSET_Y;  // 425

    // Load atlas
    std::string base = SDL_GetBasePath();
    AtlasManager::Get().Load(mRenderer,
        base + "Assets/atlas.png",
        base + "Assets/atlas.json");

    // Tạo map với MAP_RENDER_SIZE thay vì MAP_SIZE
    mMapActor = new MapActor(this);
    mMapActor->SubmitStaticTiles();
    ISORenderer::Get().BuildStaticCache();
}

void IsoMapGame::UnloadData() {
    // Extra unload here
    Game::UnloadData();
}

void IsoMapGame::ProcessInput() {}

void IsoMapGame::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 8, 8, 8, 255);
    SDL_RenderClear(mRenderer);
 
    // Dynamic: clear đầu frame (map tiles đã trong static buffer)
    ISORenderer::Get().ClearDynamic();
 
    // TODO: actors dynamic submit ở đây
 
    // Flush: merge static + dynamic → render
    ISORenderer::Get().Flush(mRenderer);
 
    // Sprites thông thường (UI, HUD) lên trên
    for (auto sprite : mSprites) {
        sprite->Draw(mRenderer);
    }
 
    SDL_RenderPresent(mRenderer);
}

void IsoMapGame::Initialize(SDL_Window* window, SDL_Renderer* renderer) {
    mWindow   = window;
    mRenderer = renderer;
}