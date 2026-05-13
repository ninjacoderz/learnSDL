#include "MapActor.h"
#include "ISORenderer.h"
#include <cstdlib>
#include <cstdio>

MapActor::MapActor(Game* game)
    : Actor(game)
{
    mISOMapComp = new ISOMapComponent(this);
}

void MapActor::ActorInput(const struct InputState& state) {
    mISOMapComp->ProcessInput(state);
}

void MapActor::UpdateActor(float deltaTime) {}
