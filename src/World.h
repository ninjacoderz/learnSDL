#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"
#include "Goblin.h"

class  World
{
public:

    template <typename T, typename... Args> T& SpawnObject (Args&&... args) {
        Objects.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        return static_cast <T&> (*Objects.back());
    }

    void HandleEvent(const SDL_Event& Event) {
        for(auto& Object: Objects) {
            Object->HandleEvent(Event);
        }
    }

    void Tick(float TimeDelta) {
        for (auto& Object: Objects){
            Object->Tick(TimeDelta);
        }
    }
    
    void Render(SDL_Surface* Surface) {
        for(auto& Object: Objects) {
            Object->Render(Surface);
        }
    }

    Goblin& SpawnGoblin(const std::string& Name, int x, int y) {
        Objects.emplace_back(
            std::make_unique<Goblin>(Name,x,y)
        );
        return static_cast<Goblin&>(*Objects.back());
    }
    
private:
    std::vector<std::unique_ptr<GameObject>> Objects;
};
