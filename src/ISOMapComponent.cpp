#include "ISOMapComponent.h"
#include "SpriteComponent.h"
#include "GameMath.h"
#include "Actor.h"

#include <SDL3/SDL.h>
#include "Defs.h"
#include "AtlasManager.h"
#include "ISORenderer.h"
#include "InputSystem.h"

ISOMapComponent::ISOMapComponent(Actor *owner, int drawOrder): 
    SpriteComponent(owner, drawOrder)
{  
    
    for (int x = 0; x < MAP_RENDER_SIZE; x++) {
        for (int z = 0; z < MAP_RENDER_SIZE; z++) {
            if (x > 14 && x < 20) {
                mMap[x][z] = rand() % 3;       // grass: 0,1,2
            } else {
                mMap[x][z] = 10 + rand() % 3;  // stone: 10,11,12
            }
        }
    }
    LoadISOMap();
}

void ISOMapComponent::Draw(SDL_Renderer *renderer)
{
    auto& iso   = ISORenderer::Get();
    iso.Flush(renderer);
}

std::string ISOMapComponent::TileIndexToFilename(int index) {
    char buf[64];
    snprintf(buf, sizeof(buf), "gfx/tiles/%d.png", index);
    return std::string(buf);
}

void ISOMapComponent::LoadISOMap() {

    auto& atlas = AtlasManager::Get();
    auto& iso   = ISORenderer::Get();
    iso.ClearStatic();

    for (int x = 0; x < MAP_RENDER_SIZE; x++) {
        for (int z = 0; z < MAP_RENDER_SIZE; z++) {
            std::string filename = TileIndexToFilename(mMap[x][z]);
            const AtlasEntry* entry = atlas.GetEntry(filename);

            if(x == mSelectedX && z == mSelectedY) {
                std::string filename = "gfx/tiles/exit.png";
                entry = atlas.GetEntry(filename);
            }
            if (!entry) return;

            iso.SubmitStatic(x, z,
                             atlas.GetTexture(),
                             entry->srcRect);
        }
    }
    iso.BuildStaticCache();
    SDL_Log("MapActor: submitted %d static tiles", MAP_RENDER_SIZE * MAP_RENDER_SIZE);

}

void ISOMapComponent::ProcessInput(const InputState& state) {

    float mx = (float)state.Mouse.GetPosition().x;
    float my = (float)state.Mouse.GetPosition().y;

    float sx = mx - MAP_RENDER_OFFSET_X ;
    float sy = my - MAP_RENDER_OFFSET_Y - TILE_HEIGHT/2;

    int selectedX = (int)floor(sx / (TILE_WIDTH) - sy / (TILE_HEIGHT));
    int selectedY = (int)floor(sx / (TILE_WIDTH) + sy / (TILE_HEIGHT));

    if (selectedX < 0 || selectedX >= MAP_RENDER_SIZE ||
        selectedY < 0 || selectedY >= MAP_RENDER_SIZE) return;
    if(mSelectedX != selectedX || mSelectedY != selectedY) {
        mSelectedX = selectedX;
        mSelectedY = selectedY;
        LoadISOMap();
    }
   
}

// void ISOMapComponent::ProcessInput(const InputState& state) {

//     int mx = (int)state.Mouse.GetPosition().x;
//     int my = (int)state.Mouse.GetPosition().y;

//     int sx = mx - MAP_RENDER_OFFSET_X;
//     int sy = my - MAP_RENDER_OFFSET_Y;

//     mSelectedX = (int)floor((float)(sx / TILE_WIDTH) - (float)(sy / TILE_HEIGHT));
//     mSelectedY = (int)floor((float)(sx / TILE_WIDTH) + (float)(sy / TILE_HEIGHT));

//     if (mSelectedX < 0 || mSelectedX >= MAP_RENDER_SIZE || mSelectedY < 0 || mSelectedY >= MAP_RENDER_SIZE) return;

//     LoadISOMap();
// }