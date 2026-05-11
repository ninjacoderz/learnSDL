#include "MapActor.h"
#include "ISORenderer.h"
#include <cstdlib>
#include <cstdio>

MapActor::MapActor(Game* game)
    : Actor(game)
{
    GenerateMap();
}

std::string MapActor::TileIndexToFilename(int index) {
    char buf[64];
    snprintf(buf, sizeof(buf), "gfx/tiles/%d.png", index);
    return std::string(buf);
}

void MapActor::GenerateMap() {
    // Port từ initMap() trong map.c
    for (int x = 0; x < MAP_SIZE; x++) {
        for (int z = 0; z < MAP_SIZE; z++) {
            if (x > 14 && x < 20) {
                mMap[x][z] = rand() % 3;       // grass: 0,1,2
            } else {
                mMap[x][z] = 10 + rand() % 3;  // stone: 10,11,12
            }
        }
    }
}

void MapActor::SubmitStaticTiles() {
    // Submit toàn bộ map vào STATIC buffer của ISORenderer
    // Gọi 1 lần khi load, sau đó BuildStaticCache() sort 1 lần
    auto& atlas = AtlasManager::Get();
    auto& iso   = ISORenderer::Get();

    for (int x = 0; x < MAP_SIZE; x++) {
        for (int z = 0; z < MAP_SIZE; z++) {
            std::string filename = TileIndexToFilename(mMap[x][z]);
            const AtlasEntry* entry = atlas.GetEntry(filename);
            if (!entry) continue;

            iso.SubmitStatic(x, z,
                             atlas.GetTexture(),
                             entry->srcRect);
        }
    }
    SDL_Log("MapActor: submitted %d static tiles", MAP_SIZE * MAP_SIZE);
}

void MapActor::SetTile(int x, int z, int tileIndex) {
    if (x < 0 || x >= MAP_SIZE || z < 0 || z >= MAP_SIZE) return;
    mMap[x][z] = tileIndex;

    // TODO: rebuild static cache
    // ISORenderer::Get().ClearStatic();
    // SubmitStaticTiles();
    // ISORenderer::Get().BuildStaticCache();
}