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

    iso.tileW   = TILE_WIDTH;           
    iso.tileH   = TILE_HEIGHT;          
    iso.originX = MAP_RENDER_OFFSET_X;  
    iso.originY = MAP_RENDER_OFFSET_Y;  

    // Load atlas
    std::string base = SDL_GetBasePath();
    AtlasManager::Get().Load(mRenderer,
        base + "Assets/atlas.png",
        base + "Assets/atlas.json");

    mMapActor = new MapActor(this);
    mMapActor->SubmitStaticTiles();
    iso.BuildStaticCache();
}

void IsoMapGame::UnloadData() {
    // Extra unload here
    Game::UnloadData();
}

void IsoMapGame::ProcessInput() {
    mInputSystem->PrepareForUpdate();
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
				mIsRunning = false;
				break;
			case SDL_EVENT_MOUSE_WHEEL:
				mInputSystem->ProcessEvent(event);
				break;
			default:
				break;
		}
	}

	mInputSystem->Update();
	const MouseState& state = mInputSystem->GetState().Mouse;
    const Vector2 pos = state.GetPosition();
    double sx, sy;
    sx = pos.x - (TILE_WIDTH / 2);
    sy = pos.y - (TILE_HEIGHT / 2);
    sx -= MAP_RENDER_OFFSET_X;
    sy -= MAP_RENDER_OFFSET_Y;
    mMapActor->cursor.x =  round(((sx / TILE_WIDTH) - (sy / TILE_HEIGHT)));
    mMapActor->cursor.z =  round(((sx / TILE_WIDTH) + (sy / TILE_HEIGHT)));
}

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
    Game::Initialize(window, renderer);

    mInputSystem = new InputSystem();
    mInputSystem->SetRelativeMouseMode(mWindow, false);
	if (!mInputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
	}
}