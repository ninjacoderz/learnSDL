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
    SDL_Log("MapActor: submitted %d static tiles", MAP_RENDER_SIZE * MAP_RENDER_SIZE);

}

void ISOMapComponent::ProcessInput(const InputState& state) {

    // Tọa độ chuột trên màn hình
    int mx = (int)state.Mouse.GetPosition().x;
    int my = (int)state.Mouse.GetPosition().y;

    // Trừ offset để về hệ tọa độ tile-space
    int sx = mx - MAP_RENDER_OFFSET_X;
    int sy = my - MAP_RENDER_OFFSET_Y;

    // Đảo ngược phép chiếu isometric
    // Chia cho nửa kích thước tile vì đó là đơn vị chiếu
    float half_w = TILE_WIDTH  / 2.0f;
    float half_h = TILE_HEIGHT / 2.0f;

    mSelectedX = (int)floor((sx / TILE_WIDTH - sy / TILE_HEIGHT));
    mSelectedY = (int)floor((sy / TILE_HEIGHT + sx / TILE_WIDTH));

    // Giới hạn trong bản đồ
    if (mSelectedX < 0 || mSelectedX >= MAP_RENDER_SIZE || mSelectedY < 0 || mSelectedY >= MAP_RENDER_SIZE) return;

    LoadISOMap();
}
