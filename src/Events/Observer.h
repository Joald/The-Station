#ifndef THE_STATION_OBSERVER_H
#define THE_STATION_OBSERVER_H


#include <functional>

template<class T>
class Observer {
    virtual void onTrigger(T&) = 0;
};

template<class T>
class ConcreteObserver : public Observer<T> {
    using ObserveCallback = std::function<void(T&)>;
    ObserveCallback callback;

    explicit ConcreteObserver(ObserveCallback callback) : callback(callback) {}

    void onTrigger(T& t) { callback(t); }
};


#endif //THE_STATION_OBSERVER_H
