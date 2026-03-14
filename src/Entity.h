//
// Created by Binh Nguyen Thanh on 7/3/26.
//

#ifndef _ENTITY_H
#define _ENTITY_H

#pragma once
#include <SDL3/SDL.h>
#include <string>

#include "Component.h"
#include "ImageComponent.h"
#include "TransformComponent.h"
#include <ranges>

#include "Commands.h"
#include "InputComponent.h"

using namespace std;

using ComponentPtr = std::unique_ptr<Component>;
using ComponentPtrList = std::vector<ComponentPtr>;

class Entity {
public:
    virtual ~Entity() = default;

    Entity(string Name) : Name(Name) {
    };

    virtual void Update(float DeltaTime) {
        for (ComponentPtr &Component: Components) {
            Component->Update(DeltaTime);
        }
    };

    virtual void Render(SDL_Surface *surface) {
        for (ComponentPtr &Component: Components) {
            Component->Render(surface);
        }
    };

    virtual void HandleEvent(const SDL_Event &event) {
        for (ComponentPtr &Component: Components) {
            Component->HandleEvent(event);
        }
    };

    template<typename CType, typename... CArgs>
        requires std::derived_from<CType, Component>
    CType *AddComponent(CArgs &&... ConstructorArgs) {
        ComponentPtr &NewComponent = Components.emplace_back(
            std::make_unique<CType>(
                std::forward<CArgs>(ConstructorArgs)...
            )
        );
        return static_cast<CType *>(NewComponent.get());
    }

    template<typename CType>
        requires std::derived_from<CType, Component>
    CType *GetComponent() {
        for (const ComponentPtr &C: Components) {
            // Try to cast the base Component pointer
            // to a CType pointer
            if (auto Ptr{dynamic_cast<CType *>(C.get())}) {
                // Cast successful, we found it!
                return Ptr;
            }
        }

        // Went through all components, didn't
        // find a CType component
        return nullptr;
    }

    template<typename CType>
        requires std::derived_from<CType, Component>
    std::vector<CType*> GetComponents() {
        std::vector<CType *> Results;
        for (const ComponentPtr &C: Components) {
            if (auto Ptr{dynamic_cast<CType *>(C.get())}) {
                Results.push_back(Ptr);
            }
        }
        return Results;
    }

    TransformComponent *AddTransformComponent() {
        if (GetTransformComponent()) {
            std::cout << "Error: Cannot have "
                    "multiple transform components";
            return nullptr;
        }
        ComponentPtr &Component = Components.emplace_back( std::make_unique<TransformComponent>(this ));
        return dynamic_cast<TransformComponent *>(Component.get());
    }

    TransformComponent *GetTransformComponent() {
        for (ComponentPtr &Component: Components) {
            if (auto Ptr = dynamic_cast<TransformComponent *>(Component.get())) {
                return Ptr;
            }
        }
        return nullptr;
    }

    void RemoveComponent(Component *PtrToRemove) {
        for (int i = 0; i < Components.size(); ++i) {
            if (Components[i].get() == PtrToRemove) {
                for (ComponentPtr& C : Components) {
                    C->OnComponentRemoved(PtrToRemove);
                }
                Components.erase(Components.begin() + i);
                return;
            }
        }
        std::cout << "Warning: Attempted to remove "
                "a component not found on this entity.\n";
    }

    ImageComponent *AddImageComponent(const std::string& FilePath) {
        ComponentPtr& Component = Components.emplace_back(
            std::make_unique<ImageComponent>(this, FilePath)
        );
        Component->Initialize();
        return static_cast<ImageComponent *>(Component.get());
    }

    using ImageComponents = std::vector<ImageComponent*>;
    ImageComponents GetImageComponents() const {
        ImageComponents Result;
        std::cout << "Ok"<< Components.size();
        for (const ComponentPtr& C : Components) {
            std::cout << "Ok";
            if (auto Ptr{dynamic_cast<
              ImageComponent*>(C.get())}
            ) {
                Result.push_back(Ptr);
            }
        }
        return Result;
    }

    InputComponent *AddInputComponent() {
        if (GetInputComponent()) {
            std::cout << "Error: Cannot have "
                "multiple input components";
            return nullptr;
        }
        std::unique_ptr<Component>& Component = Components.emplace_back(std::make_unique<InputComponent>(this));
        Component->Initialize();
        return dynamic_cast<InputComponent *>(Component.get());
    }

    InputComponent* GetInputComponent() const {
        for (const ComponentPtr& Component: Components) {
            if (auto Ptr = dynamic_cast<InputComponent *>(Component.get())) {
                return Ptr;
            }
        }
        return nullptr;
    }

    virtual void HandleCommand(std::unique_ptr<Command> Cmd) {
        Cmd->Execute(this);
    }

    string GetName() { return Name; };

private:
    string Name;
    ComponentPtrList Components;
};

class Wall : public Entity {
public:
    using Entity::Entity;

    void Update(float DeltaTime) override {
        Physics.Update(DeltaTime);
    };

private:
    PhysicsComponent Physics = PhysicsComponent(this);
};

class Fire : public Entity {
public:
    using Entity::Entity;

    void Update(float DeltaTime) override {
        Animation.Update(DeltaTime);
        Audio.Update(DeltaTime);
    };

private:
    AnimationComponent Animation = AnimationComponent(this);
    AudioComponent Audio = AudioComponent(this);
};

class Monster : public Entity {
public:
    using Entity::Entity;

    void Update(float DeltaTime) override {
        Animation.Update(DeltaTime);
        Audio.Update(DeltaTime);
        Physics.Update(DeltaTime);
    };

private:
    AnimationComponent Animation = AnimationComponent(this);
    AudioComponent Audio = AudioComponent(this);
    PhysicsComponent Physics = PhysicsComponent(this);
};

#endif //_ENTITY_H
