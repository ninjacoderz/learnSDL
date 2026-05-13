
#pragma once
#include "GameMath.h"
#include <vector>

class Actor
{
    public:
        enum State
        {
            EActive,
            EPaused,
            EDead
        };
        Actor(class Game* game);
        virtual ~Actor();

        // Update function called from Game (not overridable)
        void Update(float deltaTime);
        void UpdateComponents(float deltaTime);
        virtual void UpdateActor(float deltaTime);

        // Getters/setters
        class Game* GetGame() { return mGame; }
        const Vector2& GetPosition() const { return mPosition; }
        void SetPosition(const Vector2& pos) { mPosition = pos; }
        float GetScale() const { return mScale; }
        void SetScale(float scale) { mScale = scale; }
        float GetRotation() const { return mRotation; }
        void SetRotation(float rotation) { mRotation = rotation; }  
        State GetState() const { return mState; }
        void SetState(State state) { mState = state; }

        // Add/remove components
        void AddComponent(class Component* component);
        void RemoveComponent(class Component* component);
        virtual void ProcessInput(const struct InputState& state);
        virtual void ActorInput(const struct InputState &state);

    protected:
        class Game* mGame;
    private:
        State mState;
        // Transform
        Vector2 mPosition;
        float mScale;
        float mRotation;

        std::vector<class Component*> mComponents;
};