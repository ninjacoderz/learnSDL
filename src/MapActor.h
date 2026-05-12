#pragma once
#include "Actor.h"
#include "AtlasManager.h"
#include <string>

static constexpr int MAP_SIZE = 32;

struct Cursor{
    int x;
    int z;
};

class MapActor : public Actor {
public:
    MapActor(Game* game);
    ~MapActor() = default;

    void GenerateMap();

    // Dùng khi load: submit vào STATIC buffer → sort 1 lần
    void SubmitStaticTiles();

    // Dùng khi map thay đổi runtime: rebuild static buffer
    void SetTile(int x, int z, int tileIndex);
    Cursor cursor;
protected:
    // UpdateActor chỉ submit dynamic objects (player, effects)
    // Map tĩnh không cần làm gì ở đây
    void UpdateActor(float deltaTime) override {}

private:
    static std::string TileIndexToFilename(int index);
    int  mMap[MAP_SIZE][MAP_SIZE] = {};
};