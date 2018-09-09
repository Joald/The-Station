#ifndef THE_STATION_OBSERVABLE_H
#define THE_STATION_OBSERVABLE_H


#include <set>
#include <memory>
#include "Observer.h"

template<class T>
class Observable {
    using ObserverPointer = std::shared_ptr<Observer<T>>;
    std::set<ObserverPointer> observers;
protected:
    void trigger(T& t) {
        for (auto& observer : observers) {
            observer->onTrigger(t);
        }
    }

public:
    void registerObserver(ObserverPointer observer) {
        observers.insert(observer);
    }

    void deregisterObserver(ObserverPointer observer) {
        observers.erase(observer);
    }
};


#endif //THE_STATION_OBSERVABLE_H
