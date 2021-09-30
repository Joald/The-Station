#ifndef THE_STATION_GAME_OPTION_H
#define THE_STATION_GAME_OPTION_H

#include <string>
#include <functional>
#include "GameObject.h"
#include "Events/Observable.h"

enum class OptionState {
    OFF = 0,
    ON = 1,
};

class GameOption : public Observable<bool> {
    const std::string name;
    OptionState state;
public:
    GameOption(std::string name, OptionState state) : name(std::move(name)), state(state) {}

    void setState(OptionState newState) {
        state = newState;
    }

    void toggleState() {
        state = *this ? OptionState::OFF : OptionState::ON;
    }

    [[nodiscard]] OptionState getState() const {
        return state;
    }

    explicit operator bool() const {
        return state == OptionState::ON;
    }

    [[nodiscard]] std::string_view getName() const {
        return name;
    }
};

struct OptionComparator {
    bool operator()(const GameOption& lhs, const GameOption& rhs) const {
        return lhs.getName() < rhs.getName();
    }
};


#endif //THE_STATION_GAME_OPTION_H
