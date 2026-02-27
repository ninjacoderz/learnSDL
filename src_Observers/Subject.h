#pragma once
#include <vector>
#include "Observer.h"
template <typename EventType>
class Subject {
    public:
        int AddObserver(Observer<EventType>* observer) {
            Observers.push_back(observer);
            return NextObserverKey++;
        }
        void RemoveObserver(int id) {
            if (id >= 0 && id < Observers.size()) {
                Observers[id] = nullptr;
            }
        }
    protected:
        void NotifyObservers(const EventType& event) {
            for (auto& Obs : Observers) {
                if (Obs) Obs->OnNotify(event);
            }
        }
    private:
        std::vector<Observer<EventType>*> Observers;
        int NextObserverKey{0};
};