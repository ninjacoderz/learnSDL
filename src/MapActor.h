#pragma once
#include "Actor.h"
#include "AtlasManager.h"
#include <string>
#include "ISOMapComponent.h"
class MapActor : public Actor {
public:
    MapActor(Game* game);
    void ActorInput(const struct InputState& state) override;
    void UpdateActor(float deltaTime) override;
private:
    ISOMapComponent* mISOMapComp;
};