#ifndef THE_STATION_OBSERVER_H
#define THE_STATION_OBSERVER_H


#include <functional>

template<class T>
class Observer {
    virtual void onTrigger(T&) = 0;
};

template<class T>
class ConcreteObserver : public Observer<T> {
    typedef std::function<void(T&)> observeCallback;
    observeCallback callback;

    explicit ConcreteObserver(observeCallback callback) : callback(callback) {}

    void onTrigger(T& t) { callback(t); }
};


#endif //THE_STATION_OBSERVER_H
